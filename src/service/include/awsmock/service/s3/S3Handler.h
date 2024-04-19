//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_HANDLER_H
#define AWSMOCK_SERVICE_S3_HANDLER_H

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/dto/common/UserAgent.h>
#include <awsmock/dto/common/S3ClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/s3/S3Service.h>
#include <awsmock/service/s3/S3CmdHandler.h>

namespace AwsMock::Service {

  /**
   * AWS S3 mock handler
   *
   * <p>AWS S3 HTTP request handler. All S3 related REST call are ending here. Depending on the request header the S3 module will be selected in case the
   * authorization header contains the S3 module.<p>
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
   * <p>
   * The S3 client should not use checksum validation, as checksums are not calculated correctly yet.
   * <pre>
   *    s3Client = S3Client.builder()
   *             .credentialsProvider(ProfileCredentialsProvider.create())
   *             .region(Region.US_EAST_1)
   *             .endpointOverride(new URI(endpoint))
   *             .forcePathStyle(true)
   *             .serviceConfiguration(S3Configuration.builder().checksumValidationEnabled(false).build())
   *             .build();
   * </pre>
   * and for the async client:
   * <pre>
   *   s3AsyncClient = S3CrtAsyncClient.builder()
   *             .credentialsProvider(ProfileCredentialsProvider.create())
   *             .checksumValidationEnabled(false)
   *             .region(Region.US_EAST_1)
   *             .endpointOverride(new URI(endpoint))
   *             .forcePathStyle(true)
   *             .build();
   * </pre>
   */
  class S3Handler : public S3CmdHandler {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    S3Handler(Core::Configuration &configuration, Core::MetricService &metricService);

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
     * S3 handler configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * S3 module
     */
    Service::S3Service _s3Service;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_S3_HANDLER_H
