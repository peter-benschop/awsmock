//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_HANDLER_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_HANDLER_H

// Poco includes
#include <Poco/Condition.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/dto/common/SecretsManagerClientCommand.h>
#include "awsmock/service/common/AbstractHandler.h"
#include <awsmock/service/secretsmanager/SecretsManagerService.h>
#include <awsmock/service/secretsmanager/SecretsManagerCmdHandler.h>

namespace AwsMock::Service {

  /**
   * AWS secrets manager mock handler.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class SecretsManagerHandler : public SecretsManagerCmdHandler {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    SecretsManagerHandler(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * HTTP POST request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param region AWS region
     * @param user AWS user
     * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SECRETSMANAGER_HANDLER_H
