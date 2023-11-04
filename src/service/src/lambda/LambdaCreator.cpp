//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/LambdaCreator.h>

namespace AwsMock::Service {

  LambdaCreator::LambdaCreator(Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationQueue &createQueue)
      : _logger(Poco::Logger::get("LambdaCreator")), _configuration(configuration), _metricService(metricService), _dockerService(configuration),
        _createQueue(createQueue) {
    _lambdaDatabase = std::make_shared<Database::LambdaDatabase>(_configuration);

    _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
    _tempDir = _dataDir + Poco::Path::separator() + "tmp";
  }

  void LambdaCreator::run() {
    log_debug_stream(_logger) << "Lambda create notification received, queueSize:" << _createQueue.size() << std::endl;
    Poco::AutoPtr<Poco::Notification> pNf(_createQueue.waitDequeueNotification());
    while (pNf) {
      auto *pWorkNf = dynamic_cast<Dto::Lambda::CreateNotification *>(pNf.get());
      if (pWorkNf) {
        CreateLambdaFunction(pWorkNf->zipFileContent, pWorkNf->functionId);
      }
      pNf = _createQueue.waitDequeueNotification();
    }
  }

  void LambdaCreator::CreateLambdaFunction(const std::string &functionCode, const std::string &functionId) {
    Core::LogStream logger(Poco::Logger::get("LambdaCreator"));
    log_debug_stream(logger) << "Start creating lambda function, oid: " << functionId << std::endl;

    // Make local copy
    Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase->GetLambdaById(functionId);

    // Docker tag
    std::string dockerTag = "latest";
    if (lambdaEntity.HasTag("tag")) {
      dockerTag = lambdaEntity.GetTagValue("tag");
    }
    log_debug_stream(logger) << "Using docker tag: " << dockerTag << std::endl;

    // Build the docker image, if not existing
    if (!_dockerService.ImageExists(lambdaEntity.function, dockerTag)) {
      CreateDockerImage(functionCode, lambdaEntity, dockerTag);
    }

    // Create the container, if not existing. If existing get the current port from the docker container
    if (!_dockerService.ContainerExists(lambdaEntity.function, dockerTag)) {
      lambdaEntity.hostPort = GetHostPort();
      CreateDockerContainer(lambdaEntity, dockerTag);
    }

    // Get docker container
    Dto::Docker::Container container = _dockerService.GetContainerByName(lambdaEntity.function, dockerTag);

    // Start docker container, in case it is not already running. If already running get current public port.
    if(container.state != "running") {
      _dockerService.StartDockerContainer(container.id);
    } else {
      lambdaEntity.hostPort = container.GetLambdaPort();
    }

    // Update database
    lambdaEntity.containerId = container.id;
    lambdaEntity.lastStarted = Poco::DateTime();
    lambdaEntity.state = Database::Entity::Lambda::LambdaState::Active;
    lambdaEntity.stateReason = "Activated";
    _lambdaDatabase->UpdateLambda(lambdaEntity);

    log_debug_stream(logger) << "Lambda function started: " << lambdaEntity.function << ":" << dockerTag << std::endl;
  }

  void LambdaCreator::CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

    if (zipFile.empty()) {
      log_error_stream(_logger) << "Empty lambda zip file" << std::endl;
      return;
    }

    // Unzip provided zip-file into a temporary directory
    std::string codeDir = UnpackZipFile(zipFile, lambdaEntity.runtime, lambdaEntity.fileName);
    log_debug_stream(_logger) << "Lambda file unzipped, codeDir: " << codeDir << std::endl;

    // Build the docker image using the docker service
    std::string imageFile = _dockerService.BuildImage(codeDir, lambdaEntity.function, dockerTag, lambdaEntity.handler, lambdaEntity.runtime, lambdaEntity.environment.variables);

    // Get the image struct
    Dto::Docker::Image image = _dockerService.GetImageByName(lambdaEntity.function, dockerTag);
    lambdaEntity.codeSize = image.size;
    lambdaEntity.imageId = image.id;
    lambdaEntity.codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);
    lambdaEntity.hostPort = GetHostPort();

    // Cleanup
    Core::DirUtils::DeleteDirectory(codeDir);
    log_debug_stream(_logger) << "Docker image created, name: " << lambdaEntity.function << " size: " << lambdaEntity.codeSize << std::endl;
    log_debug_stream(_logger) << "Using port: " << lambdaEntity.hostPort << std::endl;
  }

  void LambdaCreator::CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

    try {
      std::vector<std::string> environment = GetEnvironment(lambdaEntity.environment);
      Dto::Docker::CreateContainerResponse
          containerCreateResponse = _dockerService.CreateContainer(lambdaEntity.function, dockerTag, environment, lambdaEntity.hostPort);
      log_debug_stream(_logger) << "Lambda container created, hostPort: " << lambdaEntity.hostPort << std::endl;
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  std::string LambdaCreator::UnpackZipFile(const std::string &zipFile, const std::string &runtime, const std::string &fileName) {

    // If we do not have a local file already, write the Base64 encoded file to lambda dir
    if (!Core::FileUtils::FileExists(fileName)) {
      std::ofstream ofs(fileName);
      ofs << zipFile;
      ofs.flush();
      ofs.close();
    }

    std::string decodedZipFile = Core::Crypto::Base64Decode(zipFile);

    // Create directory
    try {
      std::string codeDir = Core::DirUtils::CreateTempDir("/tmp");
      if (Core::StringUtils::ContainsIgnoreCase(runtime, "java")) {

        // Create classes directory
        std::string classesDir = codeDir + Poco::Path::separator() + "classes";
        Core::DirUtils::EnsureDirectory(classesDir);

        // Decompress
        std::stringstream input(decodedZipFile);
        Poco::Zip::Decompress dec(input, Poco::Path(classesDir));
        dec.decompressAllFiles();
        input.clear();
        log_debug_stream(_logger) << "ZIP file unpacked, dir: " << codeDir << std::endl;

      } else {

        // Create directory
        Core::DirUtils::EnsureDirectory(codeDir);

        // Write to temp file
        std::ofstream ofs(_tempDir + "/zipfile.zip");
        ofs << decodedZipFile;
        ofs.close();

        // Decompress
        Core::ExecResult result = Core::SystemUtils::Exec("unzip -o -d " + codeDir + " " + _tempDir + "/zipfile.zip");
        log_debug_stream(_logger) << "ZIP file unpacked, dir: " << codeDir << " result: " << result.status << std::endl;
      }
      return codeDir;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Could not unzip lambda code, error: " << exc.message() << std::endl;
    }
    return {};
  }

  std::vector<std::string> LambdaCreator::GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment) {

    std::vector<std::string> environment;
    environment.reserve(lambdaEnvironment.variables.size());
    for (const auto &variable : lambdaEnvironment.variables) {
      environment.emplace_back(variable.first + "=" + variable.second);
    }
    log_debug_stream(_logger) << "lambda runtime environment converted, size: " << environment.size() << std::endl;
    return environment;
  }

  int LambdaCreator::GetHostPort() {
    return Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
  }

  std::string LambdaCreator::GetDockerTag(const Database::Entity::Lambda::Lambda &lambda) {
    if (lambda.HasTag("version")) {
      return lambda.GetTagValue("version");
    }
    if (lambda.HasTag("dockerTag")) {
      return lambda.GetTagValue("dockerTag");
    }
    if (lambda.HasTag("tag")) {
      return lambda.GetTagValue("tag");
    }
    return "latest";
  }
} // namespace AwsMock::Service
