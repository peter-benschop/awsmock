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
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/Infrastructure.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/entity/module/Module.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SecretsManagerDatabase.h>
#include <awsmock/service/cognito/CognitoServer.h>
#include <awsmock/service/dynamodb/DynamoDbServer.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/lambda/LambdaServer.h>
#include <awsmock/service/s3/S3Server.h>
#include <awsmock/service/sns/SNSServer.h>
#include <awsmock/service/sqs/SQSServer.h>
#include <awsmock/service/transfer/TransferServer.h>

namespace AwsMock::Service {

    /**
     * @brief The ModuleService controls the different services
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleService {

      public:

        /**
         * Constructor
         *
         * @param serverMap module map
         */
        explicit ModuleService(Service::ServerMap &serverMap);

        /**
         * Return all list of all modules
         *
         * @param list of all modules
         */
        Database::Entity::Module::ModuleList ListModules();

        /**
         * Returns the running state
         *
         * @param module module name
         * @return module state
         */
        bool IsRunning(const std::string &module);

        /**
         * Starts a module
         *
         * @param name module name
         */
        Database::Entity::Module::Module StartService(const std::string &name);

        /**
         * Starts all services
         */
        void StartAllServices();

        /**
         * Restarts a module
         *
         * @param name module name
         */
        Database::Entity::Module::Module RestartService(const std::string &name);

        /**
         * Restarts all services
         */
        void RestartAllServices();

        /**
         * Stops a module
         *
         * @param name module name
         */
        Database::Entity::Module::Module StopService(const std::string &name);

        /**
         * Stops all services
         */
        void StopAllServices();

        /**
         * Exports the current infrastructure
         *
         * @param services service name list
         * @param prettyPrint JSON pretty print, if true JSON indent = 4
         * @param includeObjects include objects in the export
         * @return JSON string
         */
        static std::string ExportInfrastructure(const Dto::Common::Services &services, bool prettyPrint = false, bool includeObjects = false);

        /**
     * Import the infrastructure
     *
     * @param jsonString infrastructure JSON string
     */
        static void ImportInfrastructure(const std::string &jsonString);

        /**
         * Cleans the current infrastructure.
         *
         * <p>All SQS queues, SNS topics, S3 buckets etc. will be deleted, as well as all objects.</p>
         *
         * @param services service name list
         */
        static void CleanInfrastructure(const Dto::Common::Services &services);

        /**
         * Cleans the objects from the infrastructure.
         *
         * <p>Cleans all objects from the infrastructure. This means all SQS messages, SNS messages, S3 object keys, etc. will be deleted.</p>
         *
         * @param services service name list
         */
        static void CleanObjects(const Dto::Common::Services &services);

      private:

        /**
         * Server map
         */
        Service::ServerMap &_serverMap;

        /**
         * Module database
         */
        Database::ModuleDatabase &_moduleDatabase;

        /**
         * JSON pretty print
         */
        bool _prettyPrint;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MODULE_SERVICE_H
