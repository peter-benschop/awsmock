//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_CMD_HANDLER_H
#define AWSMOCK_SERVICE_DYNAMODB_CMD_HANDLER_H

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/dto/common/UserAgent.h>
#include <awsmock/dto/common/DynamoDbClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/dynamodb/DynamoDbService.h>

namespace AwsMock::Service {

  /**
   * AWS DynamoDB command handler
   */
  class DynamoDbCmdHandler : public virtual AbstractHandler {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     */
    DynamoDbCmdHandler(Core::Configuration &configuration);

  protected:

    /**
     * HTTP POST request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param clientCommand standardized request
     * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::DynamoDbClientCommand &clientCommand);

  private:

    /**
     * Return the command from the header or from the payload.
     *
     * @param request HTTP request
     * @param payload HTTP payload
     * @return SQS action
     */
    static std::string GetActionFromHeader(Poco::Net::HTTPServerRequest &request, const std::string &payload);

    /**
     * S3 handler configuration
     */
    Core::Configuration &_configuration;

    /**
     * DynamoDB module
     */
    Service::DynamoDbService _dynamoDbService;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_DYNAMODB_CMD_HANDLER_H
