//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_MODULE_HANDLER_H
#define AWSMOCK_RESOURCE_MODULE_HANDLER_H

// Poco includes
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/Task.h>
#include <Poco/TaskManager.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/core/monitoring/MetricServiceTimer.h>
#include <awsmock/dto/common/Infrastructure.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/entity/module/Module.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SecretsManagerDatabase.h>
#include <awsmock/resource/AbstractResource.h>
#include <awsmock/resource/HandlerException.h>
#include <awsmock/service/cognito/CognitoServer.h>
#include <awsmock/service/common/ModuleService.h>
#include <awsmock/service/dynamodb/DynamoDbServer.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/lambda/LambdaServer.h>
#include <awsmock/service/s3/S3Server.h>
#include <awsmock/service/secretsmanager/SecretsManagerServer.h>
#include <awsmock/service/sns/SNSServer.h>
#include <awsmock/service/sqs/SQSServer.h>
#include <awsmock/service/transfer/TransferServer.h>

namespace AwsMock::Manager {

    /**
     * @brief AwsMock module handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleHandler : public AwsMock::Manager::AbstractResource {

      public:

        /**
         * @brief Constructor
         *
         * @param serverMap map of services
         */
        explicit ModuleHandler(Service::ServerMap &serverMap);

      protected:

        /**
         * @brief HTTP GET request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleGet(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * @brief HTTP PUT request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handlePut(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * @brief HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * @brief Delete DELETE request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * @brief Options request.
         *
         * @param response HTTP response
         * @see AbstractResource::handleOption(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleOptions(Poco::Net::HTTPServerResponse &response) override;

        /**
         * @brief Head request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleHead(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      private:

        /**
         * Timer manager
         */
        Service::ServerMap &_serverMap;

        /**
         * Module database
         */
        std::shared_ptr<Database::ModuleDatabase> _serviceDatabase;

        /**
         * Module module
         */
        std::shared_ptr<Service::ModuleService> _moduleService;
    };

}// namespace AwsMock::Manager

#endif// AWSMOCK_RESOURCE_MODULE_HANDLER_H
