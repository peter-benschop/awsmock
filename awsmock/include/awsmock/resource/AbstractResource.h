//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_ABSTRACTRESOURCE_H
#define AWSMOCK_RESOURCE_ABSTRACTRESOURCE_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"

// Libri includes
#include "awsmock/core/Logger.h"
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/ResourceNotFoundException.h>
#include <awsmock/resource/HandlerException.h>
#include <awsmock/resource/handling/JsonAPIErrorBuilder.h>
#include <awsmock/resource/handling/JsonAPIResourceBuilder.h>

namespace AwsMock::Resource {

    /**
     * Abstract HTTP request handler
     */
    class AbstractResource : public Poco::Net::HTTPRequestHandler {

    public:
      /**
       * Default User-defined Constructor
       */
      AbstractResource();

      /**
       * Default Destructor
       */
      ~AbstractResource() override;

      /**
       * Handle requests.
       *
       * @param request HTTP request
       * @param response HTTP response
       * @see Poco::Net::HTTPRequestHandler
       */
      void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    protected:

      /**
       * It handles to Http verb GET.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

      /**
       * It handles to Http verb PUT.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

      /**
       * It handles to Http verb POST.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

      /**
       * It handles to Http verb DELETE.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user);

      /**
       * It handles to Http VERB OPTIONS.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

      /**
       * It validates required information into the Http headers.
       *
       * @param request HTTP request
       * @param response HTTP response
       */
      virtual void handleHttpHeaders(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

      /**
       * @param payload The string containing the Json data.
       * @return Only part of the payload with attributes in Poco Json Object format.
       */
      static Poco::JSON::Object::Ptr getJsonAttributesSectionObject(const std::string &);

      /*!
       * It validates a set of parameters have been set in a Json payload.
       *
       * @param jsonObject        Poco Json Object that contains payload data.
       * @param attributesNames   Attributes list to be validated.
       */
      static void assertPayloadAttributes(const Poco::JSON::Object::Ptr &, const std::list<std::string> &);

      /*!
       * It sets all the HTTP Response information based on the HTTP Code.
       *
       * @param statusCode    The HTTP Status Code.
       * @param response      Response to be handled.
       */
      static void handleHttpStatusCode(int statusCode, Poco::Net::HTTPServerResponse &);

      /**
       * Return the URL.
       *
       * @param fragment Part that it wishes to add to a URL.
       * @return A complete URL with a fragment added to its end.
       */
      std::string getUrl(const std::string &fragment);

      /**
       * It converts an exception to Json API format.
       *
       * @param exception The exception thrown.
       * @return The exception Json API formatted.
       */
      std::string toJson(const HandlerException &);

      /**
       * It converts an Libri exception to Json API format.
       *
       * @param exception the exception thrown.
       * @return the exception Json API formatted.
       */
      std::string toJson(const Core::ResourceNotFoundException &);

      /**
       * It converts an service exception to Json API format.
       *
       * @param exception the exception thrown.
       * @return the exception Json API formatted.
       */
      std::string toJson(const Core::ServiceException &exception);

      /**
       * Returns a query parameter by name.
       *
       * @param name The parameter name.
       * @return The parameter value.
       */
      std::string getQueryParameter(const std::string &);

      /**
       * Returns a path parameter by position.
       *
       * @param pos parameter position.
       * @return The parameter value.
       */
      std::string getPathParameter(int pos);

      /**
       * Returns the region and the user
       *
       * @param authorization HTTP authorization string
       * @param region AWS region
       * @param user AWS user
       * @return body string
       */
      void GetRegionUser(const std::string &authorization, std::string &region, std::string &user);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Base URL
       */
      std::string _baseUrl;

      /**
       * Request URI
       */
      std::string _requestURI;

      /**
       * Request Host
       */
      std::string _requestHost;

      /**
       * Query parameters
       */
      Poco::URI::QueryParameters _queryStringParameters;

      /**
       * Path parameters
       */
      std::vector<std::string> _pathParameter;
    };
} // namespace AwsMock

#endif // AWSMOCK_ABSTRACTRESOURCE_H
