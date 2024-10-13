//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/lambda/LambdaServer.h>

namespace AwsMock::Service {

    LambdaServer::LambdaServer(Core::PeriodicScheduler &scheduler) : AbstractServer("lambda"), _lambdaDatabase(Database::LambdaDatabase::instance()) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.lambda.monitoring.period", LAMBDA_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.lambda.worker.period", LAMBDA_DEFAULT_WORKER_PERIOD);

        // Directories
        _lambdaDir = configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
        log_debug << "Lambda directory: " << _lambdaDir;

        // Create environment
        _region = configuration.getString("awsmock.region");

        // Create lambda directory
        Core::DirUtils::EnsureDirectory(_lambdaDir);

        // Cleanup container
        CleanupContainers();

        // Cleanup instances
        CleanupInstances();

        // Start lambda monitoring update counters
        scheduler.AddTask("monitoring-lambda-counters", [this] { UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        scheduler.AddTask("lambda-remove-lambdas", [this] { RemoveExpiredLambdas(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "Lambda server initialized";
    }

    LambdaServer::~LambdaServer() {
        log_debug << "Lambda server destructor, region: " << _region;
        std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase.ListLambdas(_region);

        for (auto &lambda: lambdas) {

            // Cleanup instances
            for (const auto &instance: lambda.instances) {
                Service::DockerService::instance().StopContainer(instance.containerId);
                Service::DockerService::instance().DeleteContainer(instance.containerId);
                log_debug << "Lambda instances cleaned up, id: " << instance.containerId;
            }
            lambda.instances.clear();
            _lambdaDatabase.UpdateLambda(lambda);
            log_debug << "Lambda cleaned up, name: " << lambda.function;
        }
        log_debug << "All lambda instances cleaned up";
    }

    void LambdaServer::CleanupContainers() {
        _dockerService.PruneContainers();
        log_debug << "Docker containers cleaned up";
    }

    void LambdaServer::CleanupInstances() {

        log_debug << "Starting lambdas";
        std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase.ListLambdas(_region);

        for (auto &lambda: lambdas) {
            lambda.instances.clear();
            _lambdaDatabase.UpdateLambda(lambda);
        }
        log_debug << "Lambda instances cleaned up";
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

    void LambdaServer::RemoveExpiredLambdas() {

        // Get lambda list
        Database::Entity::Lambda::LambdaList lambdaList = _lambdaDatabase.ListLambdas();
        if (lambdaList.empty()) {
            return;
        }
        log_debug << "Lambda worker starting, count: " << lambdaList.size();

        // Get lifetime from configuration
        int lifetime = Core::Configuration::instance().getInt("awsmock.service.lambda.lifetime", LAMBDA_DEFAULT_LIFETIME);
        auto expired = std::chrono::system_clock::now() - std::chrono::minutes(lifetime);

        // Loop over lambdas and remove expired instances
        for (auto &lambda: lambdaList) {

            if (lambda.instances.empty()) {
                continue;
            }

            std::vector<Database::Entity::Lambda::Instance> toBeRemoved;
            for (const auto &instance: lambda.instances) {
                if (instance.status == Database::Entity::Lambda::InstanceIdle && instance.created < expired) {
                    log_info << "Lambda instance expired, function: " << lambda.function << " containerId: " << instance.containerId;
                    _dockerService.StopContainer({.id = instance.containerId});
                    toBeRemoved.emplace_back(instance);
                }
            }
            for (const auto &instance: toBeRemoved) {
                lambda.RemoveInstance(instance);
            }
            lambda = _lambdaDatabase.UpdateLambda(lambda);
            log_debug << "Lambda updated, function" << lambda.function << " removed: " << toBeRemoved.size();
        }
        _dockerService.PruneContainers();
        log_debug << "Lambda worker finished, count: " << lambdaList.size();
    }

    void LambdaServer::UpdateCounter() {
        log_trace << "Lambda monitoring starting";

        long lambdas = _lambdaDatabase.LambdaCount();
        _metricService.SetGauge(LAMBDA_FUNCTION_COUNT, lambdas);

        log_trace << "Lambda monitoring finished";
    }

}// namespace AwsMock::Service
