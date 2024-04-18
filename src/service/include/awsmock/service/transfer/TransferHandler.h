//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFERHANDLER_H
#define AWSMOCK_SERVICE_TRANSFERHANDLER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/transfer/TransferService.h>

namespace AwsMock::Service {

  /**
   * AWS Transfer mock handler
   *
   * <p>AWS Transfer HTTP request handler. All Transfer related REST call are ending here.<p>
   */
  class TransferHandler : public AbstractHandler {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    TransferHandler(Core::Configuration &configuration, Core::MetricService &metricService);

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
     * Get the request type.
     *
     * @param body HTTP message body
     * @return request type
     */
    std::string GetRequestType(const std::string &body);

    /**
     * Get the request target.
     *
     * @param request HTTP request
     * @return target string
     */
    static std::string GetTarget(const Poco::Net::HTTPServerRequest &request);

    /**
     * S3 handler configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * Transfer module
     */
    Service::TransferService _transferService;

  };

} // namespace AwsMock

#endif // AWSMOCK_SERVICE_TRANSFERHANDLER_H
