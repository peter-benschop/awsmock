//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_S3HANDLER_H
#define AWSMOCK_RESOURCE_S3HANDLER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/MediaType.h"
#include "Poco/JSON/Parser.h"

// Libri includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"
#include "awsmock/core/MetricServiceTimer.h"
#include "awsmock/core/MetricDefinition.h"
#include "awsmock/resource/HandlerException.h"
#include "awsmock/resource/AbstractResource.h"
#include "awsmock/service/S3Service.h"
#include "awsmock/dto/s3/CreateBucketRequest.h"
#include "awsmock/dto/s3/ListAllBucketResponse.h"
#include "awsmock/dto/s3/InitiateMultipartUploadResult.h"
#include "awsmock/dto/s3/CompleteMultipartUploadResult.h"

namespace AwsMock {

    /**
     * AWS S3 mock handler
     *
     * <p>AWS S3 HTTP request handler. All S3 related REST call are ending here. Depending on the request header the S3 service will be selected in case the
     * authorization header contains the S3 service.<p>
     *
     * <p><h3>GET Requests</h3>
     * <ul>
     * <li>S3 list command</li>
     * </ul>
     * </p>
     * <p><h3>POST Requests</h3>
     * <ul>
     * <li>Initial Multipart upload</li>
     * <li>Complete Multipart upload</li>
     * </ul>
     * <p>
     */
    class S3Handler : public AwsMock::Resource::AbstractResource {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService monitoring service
       */
      S3Handler(Core::Configuration &configuration, Core::MetricService &metricService);

    protected:

      /**
       * HTTP GET request.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see AbstractResource::handleGet(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
       */
      void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      /**
       * HTTP PUT request.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see AbstractResource::handlePut(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
       */
      void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      /**
       * HTTP POST request.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
       */
      void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      /**
       * Delete DELETE request.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
       */
      void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      /**
       * Options request.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see AbstractResource::handleOption(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
       */
      void handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    private:

      /**
       * Returns the payload as a string
       *
       * @param request HTTP request
       * @return payload as a string,
       */
      std::string GetPayload(Poco::Net::HTTPServerRequest &request);

      /**
       * Returns the bucket name from the URI
       *
       * @param uri request URI
       * @return bucket name
       */
      static std::string GetBucketFromUri(const std::string &uri);

      /**
       * Returns the object key from the URI
       *
       * @param uri request URI
       * @return object key
       */
      static std::string GetKeyFromUri(const std::string &uri);

      void GetBucketKeyFromUri(const std::string &uri, std::string &bucket, std::string &key);

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * S3 handler configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * S3 service
       */
      Service::S3Service _s3Service;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_S3HANDLER_H
