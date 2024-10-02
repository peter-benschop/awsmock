//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/server/Manager.h>

namespace AwsMock::Manager {

    void Manager::Initialize() {

        InitializeMonitoring();
        InitializeDatabase();
        log_info << "Starting " << Core::Configuration::GetAppName() << " " << Core::Configuration::GetVersion() << " pid: " << getpid()
                 << " loglevel: " << Core::Configuration::instance().getString("awsmock.service.logging.level");
        log_info << "Configuration file: " << Core::Configuration::instance().GetFilename();
        log_info << "Dockerized: " << std::boolalpha << Core::Configuration::instance().getBool("awsmock.dockerized");
    }

    void Manager::InitializeMonitoring() {
        int period = Core::Configuration::instance().getInt("awsmock.service.monitoring.period", 60);
        Monitoring::MetricService::instance().Start(period);
        Monitoring::MetricSystemCollector::instance().Start(period);
    }

    void Manager::InitializeDatabase() {

        // Get database variables
        Core::Configuration &configuration = Core::Configuration::instance();
        if (configuration.getBool("awsmock.mongodb.active")) {

            std::string name = configuration.getString("awsmock.mongodb.name", DEFAULT_MONGO_DBNAME);
            std::string host = configuration.getString("awsmock.mongodb.host", DEFAULT_MONGO_DBHOST);
            std::string user = configuration.getString("awsmock.mongodb.user", DEFAULT_MONGO_DBUSER);
            std::string password = configuration.getString("awsmock.mongodb.password", DEFAULT_MONGO_DBPWD);
            int _port = configuration.getInt("awsmock.mongodb.port", DEFAULT_MONGO_DBPORT);
            int poolSize = configuration.getInt("awsmock.mongodb.pool.size", DEFAULT_MONGO_POOL_SIZE);

            // MongoDB URL
            std::string url = "mongodb://" + user + ":" + password + "@" + host + ":" + std::to_string(_port) + "/?maxPoolSize=" + std::to_string(poolSize);
            mongocxx::uri _uri(url.c_str());

            auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
            Database::ConnectionPool &pool = Database::ConnectionPool::instance();

            // Options
            mongocxx::options::client client_options;
            auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
            client_options.server_api_opts(api);
            pool.configure(std::move(instance), bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(_uri)));
            log_info << "MongoDB database initialized";

            // Create database indexes
            Database::ModuleDatabase::instance().CreateIndexes();
            log_debug << "Database indexes created";

        } else {

            log_info << "In-memory database initialized";
        }
    }

    void Manager::StartModules() {

        Core::Configuration &configuration = Core::Configuration::instance();
        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        std::map<std::string, Database::Entity::Module::Module> existingModules = Database::ModuleDatabase::GetExisting();
        for (const auto &module: existingModules) {
            if (!moduleDatabase.ModuleExists(module.first)) {
                moduleDatabase.CreateModule({.name = module.first, .state = Database::Entity::Module::ModuleState::STOPPED, .status = Database::Entity::Module::ModuleStatus::ACTIVE});
            }
            if (configuration.has("awsmock.service." + module.first + ".active") && configuration.getBool("awsmock.service." + module.first + ".active")) {
                moduleDatabase.SetStatus(module.first, Database::Entity::Module::ModuleStatus::ACTIVE);
            }
        }
        Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules();

        // Get last module configuration
        for (const auto &module: modules) {
            if (module.name == "s3" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::S3Server>();
                _serverMap[module.name]->Start();
            } else if (module.name == "sqs" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::SQSServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "sns" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::SNSServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "lambda" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::LambdaServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "transfer" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::TransferServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "cognito" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::CognitoServer>();
                _serverMap[module.name]->Start();
            } else if (module.name == "dynamodb" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::DynamoDbServer>();
                _serverMap[module.name]->Start();
            } else if (module.name == "kms" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::KMSServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "ssm" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::SSMServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "secretsmanager" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::SecretsManagerServer>(configuration);
                _serverMap[module.name]->Start();
            } else if (module.name == "gateway" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                _serverMap[module.name] = std::make_shared<Service::GatewayServer>();
                _serverMap[module.name]->Start();
            }
            log_debug << "Module " << module.name << " started";
        }
    }

    void Manager::StopModules() {

        log_info << "Stopping services";

        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules();
        for (const auto &module: modules) {
            if (module.state == Database::Entity::Module::ModuleState::RUNNING) {
                log_info << "Stopping module: " << module.name;
                moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                if (_serverMap.contains(module.name)) {
                    _serverMap[module.name]->Stop();
                    log_debug << "Module " << module.name << " stopped";
                }
            }
        }
    }

    void Manager::Run() {

        int threads = Core::Configuration::instance().getInt("awsmock.manager.http.max.threads");
        std::string hostAddress = Core::Configuration::instance().getString("awsmock.manager.http.address");
        unsigned short port = Core::Configuration::instance().getInt("awsmock.manager.http.port");

        ManagerMonitoring managerMonitoring(60);

        // The io_context is required for all I/O
        boost::asio::io_context ioc{threads};

        // Create and launch a listening port
        auto address = boost::asio::ip::make_address(hostAddress);
        std::make_shared<Listener>(ioc, boost::asio::ip::tcp::endpoint{address, port}, _serverMap)->Run();

        // Capture SIGINT and SIGTERM to perform a clean shutdown
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait(
                [&](boost::beast::error_code const &, int) {
                    // Stop the `io_context`. This will cause `run()` to return immediately, eventually
                    // destroying the `io_context` and all the sockets in it.
                    log_info << "Manager stopped on signal";
                    ioc.stop();
                });

        boost::thread_group threadGroup;
        for (auto i = 0; i < threads; i++) {
            threadGroup.create_thread(
                    [ObjectPtr = &ioc] { return ObjectPtr->run(); });
        }
        threadGroup.join_all();

        // Stop all services
        StopModules();

        log_info << "So long, and thanks for all the fish!";
    }

}// namespace AwsMock::Manager