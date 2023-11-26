//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITOHANDLER_H
#define AWSMOCK_SERVICE_COGNITOHANDLER_H

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/service/AbstractHandler.h>
#include <awsmock/service/CognitoService.h>

namespace AwsMock::Service {

  /**
   * AWS Cognito mock handler
   */
  class CognitoHandler : public AbstractHandler {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    CognitoHandler(Core::Configuration &configuration, Core::MetricService &metricService);

  protected:

    /**
     * HTTP GET request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param region AWS region name
     * @param user AWS user
     * @see AbstractResource::handleGet(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

    /**
     * HTTP PUT request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param region AWS region name
     * @param user AWS user
     * @see AbstractResource::handlePut(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

    /**
     * HTTP POST request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param region AWS region name
     * @param user AWS user
     * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

    /**
     * Delete DELETE request.
     *
     * @param request HTTP request
     * @param response HTTP response
     * @param region AWS region name
     * @param user AWS user
     * @see AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

    /**
     * Options request.
     *
     * @param response HTTP response
     * @see AbstractResource::handleOption(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
     */
    void handleOptions(Poco::Net::HTTPServerResponse &response) override;

    /**
     * Head request.
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
     * Get the action from the request.
     *
     * <p>For cognito the action is part of the User-Agent header.
     * <pre>
     * User-Agent: aws-cli/2.13.38 Python/3.11.6 Linux/6.1.0-13-amd64 exe/x86_64.debian.12 prompt/off command/cognito-idp.list-user-pools
     * </pre>
     * </p>
     *
     * @param request HTTP request
     */
    std::string GetAction(const Poco::Net::HTTPServerRequest &request);

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * AwsMock configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * Cognito service
     */
    Service::CognitoService _cognitoService;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_COGNITOHANDLER_H
