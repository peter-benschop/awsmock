//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_SNSHANDLER_H
#define AWSMOCK_RESOURCE_SNSHANDLER_H

// Poco includes
#include "Poco/Logger.h"
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

namespace AwsMock {

    /**
     * AWS SNS mock handler
     */
    class SNSHandler : public AwsMock::Resource::AbstractResource {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService monitoring service
       */
      SNSHandler(Core::Configuration &configuration,Core::MetricService &metricService);

    protected:

      /**
       * Logger
       */
      Poco::Logger &_logger;

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
       * ImageHandler import configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;
    };
} // namespace AwsMock::Resource::Factory

#endif // AWSMOCK_RESOURCE_SNSHANDLER_H
