//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_CONTROLLER_ROUTER_H
#define AWSMOCK_CONTROLLER_ROUTER_H

// C++ standard includes
#include <map>
#include <string>

// Poco includes
#include "Poco/URI.h"
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/ClassLibrary.h"
#include "Poco/DynamicFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Notification.h"
#include "Poco/Observer.h"

// AwsMock includes
#include "awsmock/core/Logger.h"
#include "awsmock/config/Configuration.h"
#include "awsmock/resource/factory/IFactory.h"
#include "awsmock/resource/factory/Factory.h"
#include "awsmock/controller/ResourceNotFound.h"

namespace AwsMock::Controller {

    class Router : public Poco::Net::HTTPRequestHandlerFactory {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService common monitoring service
       */
      Router(Configuration &configuration, Core::MetricService &metricService);

      /**
       * Destructor
       */
      ~Router() override;

      /**
       * Add a route
       *
       * @param route request route
       * @param factory resource factory
       */
      void AddRoute(const std::string &route, const std::string &factory);

      /**
       * HTTP request handler
       *
       * @param request HTTP request
       * @return request handler or null in case of failure
       */
      Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

    private:

      /**
       * Return HTTP restful resource.
       *
       * @param service AWS service name
       * @param uri request URI
       * @return restfull resource
       */
      Poco::Net::HTTPRequestHandler *GetResource(const std::string &service, const std::string &uri);

      /**
       * Returns the AWS service, region and user from the authorization string.
       *
       * @param authInfo authorization string
       * @return service name
       */
      std::string GetService(const std::string &authInfo);

      /**
       * Logger
       */
      Poco::LogStream _logger;

      /**
       * Configuration
       */
      Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * Routing table
       */
      std::map<std::string, std::string> _routingTable;

      Poco::NotificationCenter dispatcher;
    };

} // namespace AwsMock::Controller

#endif // AWSMOCK_CONTROLLER_ROUTER_H
