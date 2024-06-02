//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_MODULE_SERVICE_H
#define AWSMOCK_SERVICE_MODULE_SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include "awsmock/core/LogStream.h"
#include "awsmock/core/config/Configuration.h"
#include "awsmock/core/exception/ServiceException.h"
#include "awsmock/dto/common/Infrastructure.h"
#include "awsmock/dto/common/Services.h"
#include "awsmock/dto/module/Module.h"
#include "awsmock/entity/module/Module.h"
#include "awsmock/repository/ModuleDatabase.h"
#include "awsmock/repository/SecretsManagerDatabase.h"
#include "awsmock/service/cognito/CognitoServer.h"
#include "awsmock/service/dynamodb/DynamoDbServer.h"
#include "awsmock/service/dynamodb/DynamoDbService.h"
#include "awsmock/service/gateway/GatewayServer.h"
#include "awsmock/service/kms/KMSServer.h"
#include "awsmock/service/lambda/LambdaServer.h"
#include "awsmock/service/s3/S3Server.h"
#include "awsmock/service/secretsmanager/SecretsManagerServer.h"
#include "awsmock/service/sns/SNSServer.h"
#include "awsmock/service/sqs/SQSServer.h"
#include "awsmock/service/transfer/TransferServer.h"

namespace AwsMock::Service {

    /**
     * @brief The ModuleService controls the different services
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleService {

      public:

        /**
         * @brief Constructor
         *
         * @param serverMap module map
         */
        explicit ModuleService(Service::ServerMap &serverMap) : _serverMap(serverMap), _moduleDatabase(Database::ModuleDatabase::instance()){};

        /**
         * @brief Return all list of all modules
         *
         * @return list of all modules
         */
        Database::Entity::Module::ModuleList ListModules();

        /**
         * @brief Starts a module
         *
         * @param modules list of modules
         * @return updated module list
         */
        Dto::Module::Module::ModuleList StartModules(Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Stops one or several modules
         *
         * @param modules module list
         * @return updated module list
         */
        Dto::Module::Module::ModuleList StopModules(Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Exports the current infrastructure
         *
         * @param modules modules name list
         * @param prettyPrint JSON pretty print, if true JSON indent = 4
         * @param includeObjects include objects in the export
         * @return JSON string
         */
        static std::string ExportInfrastructure(const Dto::Module::Module::ModuleList &modules, bool prettyPrint = false, bool includeObjects = false);

        /**
         * @brief Import the infrastructure
         *
         * @param jsonString infrastructure JSON string
         */
        static void ImportInfrastructure(const std::string &jsonString);

        /**
         * @brief Cleans the current infrastructure.
         *
         * <p>All SQS queues, SNS topics, S3 buckets etc. will be deleted, as well as all objects.</p>
         *
         * @param modules module list
         */
        static void CleanInfrastructure(const Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Cleans the objects from the infrastructure.
         *
         * <p>Cleans all objects from the infrastructure. This means all SQS resources, SNS resources, S3 object keys, etc. will be deleted.</p>
         *
         * @param modules modules list
         */
        static void CleanObjects(const Dto::Module::Module::ModuleList &modules);

      private:

        /**
         * Server map
         */
        Service::ServerMap &_serverMap;

        /**
         * Module database
         */
        Database::ModuleDatabase &_moduleDatabase;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MODULE_SERVICE_H
