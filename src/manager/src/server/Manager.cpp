//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/server/Manager.h>

namespace AwsMock::Manager {

    void CreateIndexes() {
        Database::ModuleDatabase::instance().CreateIndexes();
        log_debug << "Database indexes created";
    }

    void Manager::Initialize() const {

        InitializeDatabase();
        std::string boostVersion = BOOST_LIB_VERSION;
        Core::StringUtils::Replace(boostVersion, "_", ".");
        log_info << "Starting " << Core::Configuration::GetAppName() << " " << Core::Configuration::GetVersion() << " pid: " << Core::SystemUtils::GetPid()
                 << " loglevel: " << Core::Configuration::instance().GetValue<std::string>("awsmock.logging.level") << " boost version: " << boostVersion;
        log_info << "Configuration file: " << Core::Configuration::instance().GetFilename();
        log_info << "Dockerized: " << std::boolalpha << Core::Configuration::instance().GetValue<bool>("awsmock.dockerized");
    }

    void Manager::InitializeDatabase() const {

        // Get database variables
        if (Core::Configuration::instance().GetValue<bool>("awsmock.mongodb.active")) {

            _pool.Configure();

            // Create database indexes in a background thread
            boost::thread t{CreateIndexes};
            t.detach();

        } else {
            log_info << "In-memory database initialized";
        }
    }

    void Manager::AutoLoad() {
        if (Core::Configuration::instance().GetValue<bool>("awsmock.autoload.active")) {
            if (const std::string autoLoadDir = Core::Configuration::instance().GetValue<std::string>("awsmock.autoload.dir"); Core::DirUtils::DirectoryExists(autoLoadDir) && !Core::DirUtils::DirectoryEmpty(autoLoadDir)) {
                for (const auto &file: Core::DirUtils::ListFilesByExtension(autoLoadDir, "json")) {
                    if (const std::string jsonString = Core::FileUtils::ReadFile(file); !jsonString.empty()) {
                        Dto::Module::Infrastructure infrastructure;
                        infrastructure.FromJson(jsonString);
                        Dto::Module::ImportInfrastructureRequest importRequest;
                        importRequest.cleanFirst = false;
                        importRequest.infrastructure = infrastructure;
                        Service::ModuleService::ImportInfrastructure(importRequest);
                        log_info << "Loaded infrastructure from " << file;
                    }
                }
            } else if (const std::string autoLoadFile = Core::Configuration::instance().GetValue<std::string>("awsmock.autoload.file"); Core::FileUtils::FileExists(autoLoadFile)) {
                if (const std::string jsonString = Core::FileUtils::ReadFile(autoLoadFile); !jsonString.empty()) {
                    Dto::Module::Infrastructure infrastructure;
                    infrastructure.FromJson(jsonString);
                    Dto::Module::ImportInfrastructureRequest importRequest;
                    importRequest.cleanFirst = false;
                    importRequest.infrastructure = infrastructure;
                    Service::ModuleService::ImportInfrastructure(importRequest);
                    log_info << "Loaded infrastructure from " << autoLoadFile;
                }
            }
        }
        log_info << "Autoload finished";
    }

    void Manager::StopModules() {
        log_info << "Stopping services";

        Service::ModuleMap moduleMap = Service::ModuleMap::instance();
        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        for (const Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules(); const auto &module: modules) {
            if (module.state == Database::Entity::Module::ModuleState::RUNNING) {
                moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                if (moduleMap.HasModule(module.name)) {
                    log_info << "Stopping module: " << module.name;
                    moduleMap.GetModule(module.name)->Shutdown();
                    log_info << "Module " << module.name << " stopped";
                }
            }
        }
    }

    void Manager::LoadModulesFromConfiguration() {

        using Database::Entity::Module::ModuleStatus;

        Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();

        for (const std::map<std::string, Database::Entity::Module::Module> existingModules = Database::ModuleDatabase::GetExisting(); const auto &key: existingModules | std::views::keys) {
            log_trace << "Loading module, key: " << key << " status: " << std::boolalpha << Core::Configuration::instance().GetValue<bool>("awsmock.modules." + key + ".active");
            EnsureModuleExisting(key);
            Core::Configuration::instance().GetValue<bool>("awsmock.modules." + key + ".active") ? moduleDatabase.SetStatus(key, ModuleStatus::ACTIVE) : moduleDatabase.SetStatus(key, ModuleStatus::INACTIVE);
        }

        // Gateway
        EnsureModuleExisting("gateway");
        moduleDatabase.SetStatus("gateway", Core::Configuration::instance().GetValue<bool>("awsmock.gateway.active") ? ModuleStatus::ACTIVE : ModuleStatus::INACTIVE);

        // Monitoring
        EnsureModuleExisting("monitoring");
        moduleDatabase.SetStatus("monitoring", Core::Configuration::instance().GetValue<bool>("awsmock.monitoring.active") ? ModuleStatus::ACTIVE : ModuleStatus::INACTIVE);
    }

    void Manager::EnsureModuleExisting(const std::string &key) {

        using Database::Entity::Module::ModuleState;
        using Database::Entity::Module::ModuleStatus;

        if (!Database::ModuleDatabase::instance().ModuleExists(key)) {
            Database::Entity::Module::Module m = {.name = key, .state = ModuleState::STOPPED, .status = ModuleStatus::ACTIVE};
            Database::ModuleDatabase::instance().CreateModule(m);
        }
    }

    void Manager::CreateSharedMemorySegment() {

        // Create a managed shared memory segment.
        // shm = std::make_unique<boost::interprocess::managed_shared_memory>(boost::interprocess::create_only, "Monitoring", 65536);
    }

    void Manager::Run() {

        // Set the running flag
        _running = true;

        // Capture SIGINT and SIGTERM to perform a clean shutdown
        boost::asio::io_context ios;
        boost::asio::signal_set signals(ios, SIGINT, SIGTERM);
        signals.async_wait([&](beast::error_code const &, int) {
            // Stop the `io_context`. This will cause `run()` to return immediately,
            // eventually destroying the `io_context` and all the sockets in it.
            log_info << "Manager stopped on signal";
            StopModules();
            _running = false;
            ios.stop();
        });
        log_info << "Signal handler installed";

        // Create a shared memory segment for monitoring
        CreateSharedMemorySegment();

        Core::PeriodicScheduler scheduler(ios);
        auto monitoringServer = std::make_shared<Service::MonitoringServer>(scheduler);
        log_info << "Monitoring server started";

        // Load available modules from configuration file
        LoadModulesFromConfiguration();
        log_info << "Module configuration loaded";

        Service::ModuleMap moduleMap = Service::ModuleMap::instance();
        const Database::ModuleDatabase &moduleDatabase = Database::ModuleDatabase::instance();
        for (const Database::Entity::Module::ModuleList modules = moduleDatabase.ListModules(); const auto &module: modules) {
            log_debug << "Initializing module, name: " << module.name;
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

        // Auto load init file
        AutoLoad();

        // Start listener threads
        const int numProcs = Core::SystemUtils::GetNumberOfCores();
        for (auto i = 0; i < numProcs; i++) {
            _threadGroup.create_thread([&ios] { return ios.run(); });
        }

        // Start IO context
        ios.run();
        log_info << "So long, and thanks for all the fish!";
    }

}// namespace AwsMock::Manager
