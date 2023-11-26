//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H
#define AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/CognitoHandler.h>

namespace AwsMock::Service {

  /**
   * S3 request handler factory
   */
  class CognitoHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     */
    CognitoHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _logger(Poco::Logger::get("CognitoHandlerFactory")), _configuration(configuration), _metricService(metricService) {}

    /**
     * Create a new request handler instance.
     *
     * @param request HTTP request
     * @return HTTP request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
      log_trace_stream(_logger) << "Factory for request: " << request.getURI() << std::endl;
      return new CognitoHandler(_configuration, _metricService);
    }

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * S3 handler configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H
