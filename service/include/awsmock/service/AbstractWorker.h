//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_ABSTRACTWORKER_H
#define AWSMOCK_SERVICE_ABSTRACTWORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {
  
  class AbstractWorker {
    
    public:
      
      /**
       * Constructor
       */
      explicit AbstractWorker(const Core::Configuration &configuration);
      
      /**
       * Send a lambda create function request.
       *
       * @param url HTTP URL
       * @param body HTTP message body
       * @param contentType HTTP content type
       */
      void SendPostRequest(const std::string &url, const std::string &body, const std::string &contentType);
      
      /**
       * Send a PUT request.
       *
       * @param url HTTP URL
       * @param body HTTP message body
       * @param contentType HTTP content type
       */
      void SendPutRequest(const std::string &url, const std::string &body, const std::string &contentType);
      
      /**
       * Send a DELETE request
       *
       * @param url HTTP URL
       * @param body HTTP message body
       * @param contentType HTTP content type
       */
      void SendDeleteRequest(const std::string &url, const std::string &body, const std::string &contentType);
      
      /**
       * Send a HEAD request
       *
       * @param url HTTP URL
       * @param body HTTP message body
       * @param contentType HTTP content type
       * @return true, if status = 200
       */
      bool SendHeadRequest(const std::string &url, const std::string &contentType);
      
      /**
       * Send a lambda create function request.
       *
       * @param url HTTP URL
       * @param fileName name of the file to send
       * @param headers HTTP header map
       */
      void SendFile(const std::string &url, const std::string &fileName, const std::map <std::string, std::string> &headers);
    
    private:
      
      /**
       * Adds the authorization header.
       *
       * @param request HTTP request
       */
      void AddAuthorization(Poco::Net::HTTPRequest &request);
      
      /**
       * Logger
       */
      Core::LogStream _logger;
      
      /**
       * Configuration
       */
      const Core::Configuration &_configuration;
      
      /**
       * Service database
       */
      std::unique_ptr <Database::ServiceDatabase> _serviceDatabase;
      
      /**
       * Lambda database
       */
      std::unique_ptr <Database::LambdaDatabase> _lambdaDatabase;
      
      /**
       * S3 service
       */
      std::unique_ptr <Service::S3Service> _s3Service;
      
      /**
       * Lambda service
       */
      std::unique_ptr <Service::LambdaService> _lambdaService;
      
      /**
       * Data dir
       */
      std::string _dataDir;
      
      /**
       * AWS region
       */
      std::string _region;
      
      /**
       * Running flag
       */
      bool _running;
      
      /**
       * Sleeping period in ms
       */
      int _period;
      
      /**
       * AWS client ID
       */
      std::string _clientId;
      
      /**
       * AWS user
       */
      std::string _user;
      
      /**
       * Lambda service host
       */
      std::string _lambdaServiceHost;
      
      /**
       * Lambda service port
       */
      int _lambdaServicePort;
  };
  
} // namespace AwsMock::Worker

#endif // AWSMOCK_SERVICE_ABSTRACTWORKER_H
