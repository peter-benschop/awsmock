//
// Created by vogje01 on 06/06/2023.
//

#include "awsmock/service/module/ModuleService.h"

namespace AwsMock::Service {

    Database::Entity::Module::ModuleList ModuleService::ListModules() {

        Database::Entity::Module::ModuleList modules = _moduleDatabase.ListModules();
        log_debug << "Module list, count: " << modules.size();
        return modules;
    }

    Dto::Module::Module::ModuleList ModuleService::StartModules(Dto::Module::Module::ModuleList &modules) {

        for (auto const &m: modules) {

            // Set state
            Database::Entity::Module::Module module = _moduleDatabase.GetModuleByName(m.name);
            if (module.state != Database::Entity::Module::ModuleState::RUNNING) {

                // Set state
                module = _moduleDatabase.SetState(m.name, Database::Entity::Module::ModuleState::RUNNING);

                if (module.name == "database") {
                    _moduleDatabase.StartDatabase();
                } else if (module.name == "s3") {
                    auto s3server = _serverMap[module.name];
                    s3server->Start();
                } else if (module.name == "sqs") {
                    auto sqsServer = _serverMap[module.name];
                    sqsServer->Start();
                } else if (module.name == "sns") {
                    auto snsServer = _serverMap[module.name];
                    snsServer->Start();
                } else if (module.name == "lambda") {
                    auto lambdaServer = _serverMap[module.name];
                    lambdaServer->Start();
                } else if (module.name == "transfer") {
                    auto transferServer = _serverMap[module.name];
                    transferServer->Start();
                } else if (module.name == "cognito") {
                    auto cognitoServer = _serverMap[module.name];
                    cognitoServer->Start();
                } else if (module.name == "dynamodb") {
                    auto dynamoDbServer = _serverMap[module.name];
                    dynamoDbServer->Start();
                } else if (module.name == "kms") {
                    auto kmsServer = _serverMap[module.name];
                    kmsServer->Start();
                } else if (module.name == "gateway") {
                    auto gatewayServer = _serverMap[module.name];
                    gatewayServer->Start();
                }
                log_info << "Module " << m.name << " started";
            }
        }
        return Dto::Module::Mapper::map(_moduleDatabase.ListModules());
    }

    Dto::Module::Module::ModuleList ModuleService::StopModules(Dto::Module::Module::ModuleList &modules) {

        for (auto const &m: modules) {

            // Set state
            Database::Entity::Module::Module module = _moduleDatabase.GetModuleByName(m.name);
            if (module.state == Database::Entity::Module::ModuleState::RUNNING) {

                // Set state
                module = _moduleDatabase.SetState(m.name, Database::Entity::Module::ModuleState::STOPPED);

                // Stop module
                if (m.name == "database") {
                    _moduleDatabase.StopDatabase();
                } else {
                    for (const auto &server: _serverMap) {
                        if (m.name == server.first) {
                            server.second->Stop();
                        }
                    }
                }
            }
            log_info << "Module " + m.name + " stopped";
        }

        return Dto::Module::Mapper::map(_moduleDatabase.ListModules());
    }

    std::string ModuleService::ExportInfrastructure(const Dto::Module::Module::ModuleList &modules, bool prettyPrint, bool includeObjects) {

        Dto::Common::Infrastructure infrastructure;

        for (const auto &module: modules) {

            if (module.name == "s3") {

                Database::S3Database &_s3Database = Database::S3Database::instance();
                infrastructure.s3Buckets = _s3Database.ListBuckets();
                if (includeObjects) {
                    infrastructure.s3Objects = _s3Database.ListObjects();
                }

            } else if (module.name == "sqs") {

                Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
                infrastructure.sqsQueues = _sqsDatabase.ListQueues();
                if (includeObjects) {
                    infrastructure.sqsMessages = _sqsDatabase.ListMessages();
                }

            } else if (module.name == "sns") {

                Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
                infrastructure.snsTopics = _snsDatabase.ListTopics();
                if (includeObjects) {
                    infrastructure.snsMessages = _snsDatabase.ListMessages();
                }

            } else if (module.name == "lambda") {

                Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();
                infrastructure.lambdas = _lambdaDatabase.ListLambdas();

            } else if (module.name == "cognito") {

                Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();
                infrastructure.cognitoUserPools = _cognitoDatabase.ListUserPools();
                infrastructure.cognitoUserGroups = _cognitoDatabase.ListGroups();
                infrastructure.cognitoUsers = _cognitoDatabase.ListUsers();

            } else if (module.name == "dynanomdb") {

                Database::DynamoDbDatabase &_dynamoDbDatabase = Database::DynamoDbDatabase::instance();
                infrastructure.dynamoDbTables = _dynamoDbDatabase.ListTables();
                if (includeObjects) {
                    infrastructure.dynamoDbItems = _dynamoDbDatabase.ListItems();
                }

            } else if (module.name == "secretsmanager") {

                Database::SecretsManagerDatabase &_secretsManagerDatabase = Database::SecretsManagerDatabase::instance();
                infrastructure.secrets = _secretsManagerDatabase.ListSecrets();

            } else if (module.name == "transfer") {

                Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();
                infrastructure.transferServers = _transferDatabase.ListServers();

            } else if (module.name == "kms") {

                Database::KMSDatabase &_kmsDatabase = Database::KMSDatabase::instance();
                infrastructure.kmsKeys = _kmsDatabase.ListKeys();
            }
        }
        return infrastructure.ToJson(prettyPrint);
    }

    void ModuleService::ImportInfrastructure(const std::string &jsonString) {
        log_info << "Importing services, length: " << jsonString.length();

        Dto::Common::Infrastructure infrastructure;
        infrastructure.FromJson(jsonString);

        if (!infrastructure.s3Buckets.empty() || !infrastructure.s3Objects.empty()) {
            std::shared_ptr<Database::S3Database> _s3Database = std::make_shared<Database::S3Database>();
            if (!infrastructure.s3Buckets.empty()) {
                for (const auto &bucket: infrastructure.s3Buckets) {
                    _s3Database->CreateOrUpdateBucket(bucket);
                }
                log_info << "S3 buckets imported, count: " << infrastructure.s3Buckets.size();
            }
            if (!infrastructure.s3Objects.empty()) {
                for (const auto &object: infrastructure.s3Objects) {
                    _s3Database->CreateOrUpdateObject(object);
                }
                log_info << "S3 objects imported, count: " << infrastructure.s3Objects.size();
            }
        }
        if (!infrastructure.sqsQueues.empty() || !infrastructure.sqsMessages.empty()) {
            Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
            if (!infrastructure.sqsQueues.empty()) {
                for (auto &queue: infrastructure.sqsQueues) {
                    _sqsDatabase.CreateOrUpdateQueue(queue);
                    log_debug << "SQS queues imported, url: " << queue.queueUrl;
                }
                log_info << "SQS queues imported, count: " << infrastructure.sqsQueues.size();
            }
            if (!infrastructure.sqsMessages.empty()) {
                for (auto &message: infrastructure.sqsMessages) {
                    _sqsDatabase.CreateOrUpdateMessage(message);
                    log_debug << "SQS queues imported, queueArn: " << message.queueArn;
                }
                log_info << "SQS resources imported, count: " << infrastructure.sqsMessages.size();
            }
        }
        if (!infrastructure.snsTopics.empty() || !infrastructure.snsMessages.empty()) {
            Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
            if (!infrastructure.snsTopics.empty()) {
                for (auto &topic: infrastructure.snsTopics) {
                    _snsDatabase.CreateOrUpdateTopic(topic);
                }
                log_info << "SNS topics imported, count: " << infrastructure.snsTopics.size();
            }
            if (!infrastructure.snsMessages.empty()) {
                for (auto &message: infrastructure.snsMessages) {
                    _snsDatabase.CreateOrUpdateMessage(message);
                }
                log_info << "SNS resources imported, count: " << infrastructure.snsMessages.size();
            }
        }
        if (!infrastructure.lambdas.empty()) {
            Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();
            for (auto &lambda: infrastructure.lambdas) {
                _lambdaDatabase.CreateOrUpdateLambda(lambda);
            }
            log_info << "Lambda functions imported, count: " << infrastructure.lambdas.size();
        }
        if (!infrastructure.transferServers.empty()) {
            Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();
            for (auto &transfer: infrastructure.transferServers) {
                _transferDatabase.CreateOrUpdateTransfer(transfer);
            }
            log_info << "Transfer servers imported, count: " << infrastructure.transferServers.size();
        }

        // Cognito
        if (!infrastructure.cognitoUserPools.empty() || !infrastructure.cognitoUsers.empty()) {
            Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();
            if (!infrastructure.cognitoUserPools.empty()) {
                for (auto &userPool: infrastructure.cognitoUserPools) {
                    _cognitoDatabase.CreateOrUpdateUserPool(userPool);
                }
                log_info << "Cognito user pools imported, count: " << infrastructure.cognitoUserPools.size();
            }
            if (!infrastructure.cognitoUsers.empty()) {
                for (auto &user: infrastructure.cognitoUsers) {
                    _cognitoDatabase.CreateOrUpdateUser(user);
                }
                log_info << "Cognito users imported, count: " << infrastructure.cognitoUsers.size();
            }
        }

        // DynamoDB
        if (!infrastructure.dynamoDbTables.empty() || !infrastructure.dynamoDbItems.empty()) {
            Database::DynamoDbDatabase &_dynamoDatabase = Database::DynamoDbDatabase::instance();
            if (!infrastructure.dynamoDbTables.empty()) {
                for (auto &table: infrastructure.dynamoDbTables) {
                    _dynamoDatabase.CreateOrUpdateTable(table);
                }
                log_info << "DynamoDb tables imported, count: " << infrastructure.dynamoDbTables.size();
            }
            if (!infrastructure.dynamoDbItems.empty()) {
                for (auto &item: infrastructure.dynamoDbItems) {
                    //_dynamoDatabase->CreateOrUpdateUser(user);
                }
                log_info << "DynamoDb items imported, count: " << infrastructure.dynamoDbItems.size();
            }
        }

        // SecretsManager
        if (!infrastructure.secrets.empty()) {
            Database::SecretsManagerDatabase &_secretsDatabase = Database::SecretsManagerDatabase::instance();
            if (!infrastructure.secrets.empty()) {
                for (auto &secret: infrastructure.secrets) {
                    _secretsDatabase.CreateOrUpdateSecret(secret);
                }
                log_info << "Secrets imported, count: " << infrastructure.secrets.size();
            }
        }
    }

    void ModuleService::CleanInfrastructure(const Dto::Module::Module::ModuleList &modules) {
        log_info << "Cleaning services, length: " << modules.size();

        for (const auto &m: modules) {

            if (m.name == "s3") {
                std::shared_ptr<Database::S3Database> _s3Database = std::make_shared<Database::S3Database>();
                _s3Database->DeleteAllObjects();
                _s3Database->DeleteAllBuckets();
            } else if (m.name == "sqs") {
                Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
                _sqsDatabase.DeleteAllMessages();
                _sqsDatabase.DeleteAllQueues();
            } else if (m.name == "sns") {
                Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
                _snsDatabase.DeleteAllMessages();
                _snsDatabase.DeleteAllTopics();
            } else if (m.name == "lambda") {
                Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();
                _lambdaDatabase.DeleteAllLambdas();
            } else if (m.name == "cognito") {
                Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();
                _cognitoDatabase.DeleteAllUsers();
                _cognitoDatabase.DeleteAllUserPools();
                _cognitoDatabase.DeleteAllGroups();
            } else if (m.name == "dynamodb") {
                Service::DynamoDbService _dynamoDbService;
                //_dynamoDbService.DeleteAllItems();
                _dynamoDbService.DeleteAllTables();
            } else if (m.name == "transfer") {
                Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();
                _transferDatabase.DeleteAllTransfers();
            } else if (m.name == "secretsmanager") {
                Database::SecretsManagerDatabase &_secretsManagerDatabase = Database::SecretsManagerDatabase::instance();
                _secretsManagerDatabase.DeleteAllSecrets();
            } else if (m.name == "kms") {
                Database::KMSDatabase &_kmsDatabase = Database::KMSDatabase::instance();
                _kmsDatabase.DeleteAllKeys();
            }
        }
    }

    void ModuleService::CleanObjects(const Dto::Module::Module::ModuleList &modules) {
        log_info << "Cleaning objects, length: " << modules.size();

        for (const auto &m: modules) {
            if (m.name == "s3") {
                std::shared_ptr<Database::S3Database> _s3Database = std::make_shared<Database::S3Database>();
                _s3Database->DeleteAllObjects();
            } else if (m.name == "sqs") {
                Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
                _sqsDatabase.DeleteAllMessages();
            } else if (m.name == "sns") {
                Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
                _snsDatabase.DeleteAllMessages();
            } else if (m.name == "lambda") {
                Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();
                _lambdaDatabase.DeleteAllLambdas();
            } else if (m.name == "cognito") {
                Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();
                _cognitoDatabase.DeleteAllUsers();
                _cognitoDatabase.DeleteAllUserPools();
            } else if (m.name == "dynamodb") {
                Database::DynamoDbDatabase &_dynamoDbDatabase = Database::DynamoDbDatabase::instance();
                _dynamoDbDatabase.DeleteAllItems();
            } else if (m.name == "transfer") {
                Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();
                _transferDatabase.DeleteAllTransfers();
            } else if (m.name == "secretsmanager") {
                Database::SecretsManagerDatabase &_secretsManagerDatabase = Database::SecretsManagerDatabase::instance();
                _secretsManagerDatabase.DeleteAllSecrets();
            } else if (m.name == "kms") {
                Database::KMSDatabase &_kmsDatabase = Database::KMSDatabase::instance();
                _kmsDatabase.DeleteAllKeys();
            }
        }
    }
}// namespace AwsMock::Service
