//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/lambda/LambdaServer.h>

namespace AwsMock::Service {

    LambdaServer::LambdaServer() : AbstractServer("lambda"), _lambdaDatabase(Database::LambdaDatabase::instance()) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.lambda.monitoring.period", LAMBDA_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.lambda.worker.period", LAMBDA_DEFAULT_WORKER_PERIOD);

        // Directories
        _lambdaDir = configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
        log_debug << "Lambda directory: " << _lambdaDir;

        // Create environment
        _region = configuration.getString("awsmock.region");

        // lambda module connection
        _lambdaServiceHost = configuration.getString("awsmock.service.lambda.host", "localhost");
        _lambdaServicePort = configuration.getInt("awsmock.service.lambda.port", 9503);
        log_debug << "Lambda module endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort;

        // Create lambda directory
        Core::DirUtils::EnsureDirectory(_lambdaDir);

        // Cleanup
        CleanupContainers();

        // Start lambda monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-lambda-counters", [this] { this->_lambdaMonitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        Core::PeriodicScheduler::instance().AddTask("lambda-remove-lambdas", [this] { this->_lambdaWorker.RemoveExpiredLambdas(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "Lambda server initialized";
    }

    void LambdaServer::Initialize() {
    }

    void LambdaServer::Run() {
    }

    void LambdaServer::Shutdown() {
    }

    void LambdaServer::CleanupContainers() {
        _dockerService.PruneContainers();
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
