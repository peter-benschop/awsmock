//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_GATEWAYHANDLER_H
#define AWSMOCK_SERVICE_GATEWAYHANDLER_H

// C++ includes
#include <string>
#include <utility>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Net/HTTPClientSession.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/service/AbstractHandler.h>

namespace AwsMock::Service {

  /**
   * AWS S3 mock handler
   *
   * <p>AWS S3 HTTP request handler. All S3 related REST call are ending here. Depending on the request header the S3 service will be selected in case the
   * authorization header contains the S3 service.<p>
   *
   * <p><h3>GET Requests</h3>
   * <ul>
   * <li>S3 bucket list command: <pre>aws s3 ls --endpoint http://localhost:4567</pre></li>
   * <li>S3 object list command: <pre>aws s3 ls s3://example-bucket --recursive --endpoint http://localhost:4567</pre></li>
   * </ul>
   * </p>
   * <p><h3>POST Requests</h3>
   * <ul>
   * <li>Bigfile (>4MB) Initial Multipart upload: <pre>aws cp example.txt s3://example-bucket/test/example.txt --endpoint http://localhost:4567</pre></li>
   * <li>Upload part</li>
   * <li>Complete Multipart upload</li>
   * </ul>
   * <p>
   */
  class GatewayHandler : public AbstractHandler {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService monitoring service
       * @param host service host
       * @param port service port
       */
      GatewayHandler(Core::Configuration &configuration, Core::MetricService &metricService, std::string host, int port);

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
       * Forward request to the corresponding service
       *
       * @param request HTTP request
       * @param response HTTP response
       * @param host service host
       * @param port service port
       */
      void ForwardRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &host, int port);

      /**
       * Sets extra header values
       *
       * @param request HTTP request
       * @param region AWS region
       * @param user AWS user
       */
      void SetHeaders(Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * S3 handler configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * Service host
       */
      std::string _host;

      /**
       * Service port
       */
      int _port;

  };
} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_GATEWAYHANDLER_H
