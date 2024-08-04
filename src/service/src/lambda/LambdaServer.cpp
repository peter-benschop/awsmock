//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/lambda/LambdaServer.h>

namespace AwsMock::Service {

    LambdaServer::LambdaServer(Core::Configuration &configuration) : AbstractServer("lambda"), _configuration(configuration), _lambdaDatabase(Database::LambdaDatabase::instance()), _module("lambda") {

        // Get HTTP configuration values
        _port = _configuration.getInt("awsmock.service.lambda.http.port", LAMBDA_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.lambda.http.host", LAMBDA_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.lambda.http.max.queue", LAMBDA_DEFAULT_QUEUE);
        _maxThreads = _configuration.getInt("awsmock.service.lambda.http.max.threads", LAMBDA_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.lambda.http.timeout", LAMBDA_DEFAULT_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.lambda.monitoring.period", LAMBDA_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = _configuration.getInt("awsmock.service.lambda.worker.period", LAMBDA_DEFAULT_WORKER_PERIOD);

        // Directories
        _lambdaDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
        log_debug << "Lambda directory: " << _lambdaDir;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
        log_debug << "Lambda manager period: " << _period;

        // Create environment
        _region = _configuration.getString("awsmock.region");

        // lambda module connection
        _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
        _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
        log_debug << "Lambda module endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort;

        // Docker module
        _dockerService = std::make_unique<Service::DockerService>();

        // Monitoring
        _lambdaMonitoring = std::make_unique<LambdaMonitoring>(_monitoringPeriod);

        // Worker thread
        _lambdaWorker = std::make_unique<LambdaWorker>(_workerPeriod);

        // Create lambda directory
        Core::DirUtils::EnsureDirectory(_lambdaDir);

        // Set running
        SetRunning();

        log_debug << "Lambda server initialized";
    }

    void LambdaServer::Initialize() {

        // Check module active
        if (!IsActive("lambda")) {
            log_info << "Lambda module inactive";
            return;
        }
        log_info << "Lambda server starting";

        // Start monitoring
        _lambdaMonitoring->Start();

        // Start monitoring
        _lambdaWorker->Start();

        // Cleanup
        CleanupContainers();

        // Start all lambda functions
        // StartLambdaFunctions();
    }

    void LambdaServer::Run() {
    }

    void LambdaServer::Shutdown() {
        _lambdaMonitoring->Stop();
        _lambdaWorker->Stop();
        //       StopHttpServer();
    }

    void LambdaServer::CleanupContainers() {
        _dockerService->PruneContainers();
        log_debug << "Docker containers cleaned up";
    }

    void LambdaServer::StartLambdaFunctions() {

        log_debug << "Starting lambdas";
        std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase.ListLambdas(_region);

        Service::LambdaService lambdaService;

        for (auto &lambda: lambdas) {

            try {
                // Create function request and send to service
                Dto::Lambda::CreateFunctionRequest request = Dto::Lambda::Mapper::map(lambda);

                // Add function code
                request.code = GetCode(lambda);

                lambdaService.CreateFunction(request);
                log_debug << "Lambda started, name:" << lambda.function;

            } catch (Core::ServiceException &e) {
                log_error << e.message();
            }
        }
    }

    Dto::Lambda::Code LambdaServer::GetCode(const Database::Entity::Lambda::Lambda &lambda) {

        Dto::Lambda::Code code;

        // Check file
        if (lambda.code.zipFile.empty()) {
            throw Core::ServiceException("Lambda Zip file missing");
        }

        // Load file
        std::string filename = _lambdaDir + Poco::Path::separator() + lambda.code.zipFile;
        if (Core::FileUtils::FileExists(filename)) {

            std::stringstream ss;
            std::ifstream ifs(filename);
            ss << ifs.rdbuf();
            ifs.close();

            log_debug << "Loaded lambda from file: " << filename << " size: " << Core::FileUtils::FileSize(filename);
            return {.zipFile = ss.str()};

        } else {
            throw Core::ServiceException("Lambda Zip file does not exist");
        }
    }

}// namespace AwsMock::Service
