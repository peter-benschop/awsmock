//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/server/Manager.h>

namespace AwsMock::Manager {

    void CreateIndexes() {
        Database::ModuleDatabase::instance().CreateIndexes();
        log_debug << "Database indexes created";
    }

    void Manager::Initialize() {

        InitializeDatabase();
        log_info << "Starting " << Core::YamlConfiguration::GetAppName() << " " << Core::YamlConfiguration::GetVersion() << " pid: " << getpid()
                 << " loglevel: " << Core::YamlConfiguration::instance().GetValueString("awsmock.logging.level");
        log_info << "Configuration file: " << Core::YamlConfiguration::instance().GetFilename();
        log_info << "Dockerized: " << std::boolalpha << Core::YamlConfiguration::instance().GetValueBool("awsmock.dockerized");
    }

    void Manager::InitializeDatabase() {

        // Get database variables
        if (const Core::YamlConfiguration &configuration = Core::YamlConfiguration::instance(); configuration.GetValueBool("awsmock.mongodb.active")) {

            const std::string name = configuration.GetValueString("awsmock.mongodb.name");
            const std::string host = configuration.GetValueString("awsmock.mongodb.host");
            const std::string user = configuration.GetValueString("awsmock.mongodb.user");
            const std::string password = configuration.GetValueString("awsmock.mongodb.password");
            const int _port = configuration.GetValueInt("awsmock.mongodb.port");
            const int poolSize = configuration.GetValueInt("awsmock.mongodb.pool-size");

            // MongoDB URL
            const std::string url = "mongodb://" + user + ":" + password + "@" + host + ":" + std::to_string(_port) + "/?maxPoolSize=" + std::to_string(poolSize);
            mongocxx::uri _uri(url.c_str());

            auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
            Database::ConnectionPool &pool = Database::ConnectionPool::instance();

            // Options
            const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
            pool.configure(std::move(instance), bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(_uri)));
            log_info << "MongoDB database initialized, version: " << mongocxx::v_noabi::options::server_api::version_to_string(api.get_version());

            // Create database indexes in a background thread
            boost::thread t{CreateIndexes};
            t.detach();

        } else {

            log_info << "In-memory database initialized";
        }
    }

    void Manager::StopModules() {

        log_info << "Stopping services";

        Service::ModuleMap moduleMap = Service::ModuleMap::instance();
        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        for (Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules(); const auto &module: modules) {
            if (module.state == Database::Entity::Module::ModuleState::RUNNING) {
                log_info << "Stopping module: " << module.name;
                moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                if (moduleMap.HasModule(module.name)) {
                    moduleMap.GetModule(module.name)->Shutdown();
                    log_debug << "Module " << module.name << " stopped";
                }
            }
        }
    }

    void Manager::Run() {

        const Core::YamlConfiguration &configuration = Core::YamlConfiguration::instance();
        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        for (const std::map<std::string, Database::Entity::Module::Module> existingModules = Database::ModuleDatabase::GetExisting(); const auto &module: existingModules) {
            if (!moduleDatabase.ModuleExists(module.first)) {
                Database::Entity::Module::Module m = {.name = module.first, .state = Database::Entity::Module::ModuleState::STOPPED, .status = Database::Entity::Module::ModuleStatus::ACTIVE};
                moduleDatabase.CreateModule(m);
            }
            if (configuration.GetValueBool("awsmock.modules." + module.first + ".active")) {
                moduleDatabase.SetStatus(module.first, Database::Entity::Module::ModuleStatus::ACTIVE);
            }
        }
        Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules();

        // Define thread pool size
        const int numberOfCores = Core::SystemUtils::GetNumberOfCores();
        boost::asio::thread_pool pool(numberOfCores);

        // Capture SIGINT and SIGTERM to perform a clean shutdown
        boost::asio::io_service ios;

        Core::PeriodicScheduler scheduler(ios);
        auto monitoringServer = std::make_shared<Service::MonitoringServer>(scheduler);

        boost::asio::signal_set signals(ios, SIGINT, SIGTERM);
        signals.async_wait(
                [&](boost::beast::error_code const &, int) {
                    // Stop the `io_context`. This will cause `run()` to return immediately, eventually
                    // destroying the `io_context` and all the sockets in it.
                    log_info << "Manager stopped on signal";
                    StopModules();
                    pool.stop();
                    ios.stop();
                });

        Service::ModuleMap moduleMap = Service::ModuleMap::instance();
        for (const auto &module: modules) {
            if (module.name == "gateway" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::GatewayServer>(ios));
            } else if (module.name == "s3" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::S3Server>(scheduler));
            } else if (module.name == "sqs" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::SQSServer>(scheduler));
            } else if (module.name == "sns" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::SNSServer>(scheduler));
            } else if (module.name == "lambda" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::LambdaServer>(scheduler));
            } else if (module.name == "transfer" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::TransferServer>(scheduler));
            } else if (module.name == "cognito" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::CognitoServer>(scheduler));
            } else if (module.name == "dynamodb" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::DynamoDbServer>(scheduler));
            } else if (module.name == "kms" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::KMSServer>(scheduler));
            } else if (module.name == "ssm" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::SSMServer>(scheduler));
            } else if (module.name == "secretsmanager" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                moduleMap.AddModule(module.name, std::make_shared<Service::SecretsManagerServer>(scheduler));
            }
        }

        for (auto i = 0; i < numberOfCores; i++) {
            _threadGroup.create_thread([ObjectPtr = &ios] { return ObjectPtr->run(); });
        }
        ios.run();
        log_info << "So long, and thanks for all the fish!";
    }

}// namespace AwsMock::Manager