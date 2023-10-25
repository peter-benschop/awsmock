//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_MODULEHANDLER_H
#define AWSMOCK_RESOURCE_MODULEHANDLER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/JSON/JSON.h"
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/service/S3Server.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/resource/HandlerException.h>
#include <awsmock/resource/AbstractResource.h>

#define MODULE_DEFAULT_HOST "localhost"
#define MODULE_DEFAULT_PORT 9600

namespace AwsMock {

  /**
   * AwsMock module handler
   */
  class ModuleHandler : public AwsMock::Resource::AbstractResource {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService monitoring service
       */
      ModuleHandler(Core::Configuration &configuration, Core::MetricService &metricService);

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
       * Module database
       */
      std::shared_ptr<Database::ModuleDatabase> _serviceDatabase;
  };

} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_MODULEHANDLER_H
