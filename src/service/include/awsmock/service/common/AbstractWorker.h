//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_ABSTRACT_WORKER_H
#define AWSMOCK_SERVICE_ABSTRACT_WORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/repository/LambdaDatabase.h"
#include "awsmock/repository/ModuleDatabase.h"
#include "awsmock/service/s3/S3Service.h"

namespace AwsMock::Service {

    /**
     * Abstract HTTP request worker
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class AbstractWorker {

      public:

        /**
         * Constructor
         */
        explicit AbstractWorker(const Core::Configuration &configuration);

        /**
         * Send a lambda create function request.
         *
         * @param module AwsMock module name
         * @param url HTTP URL
         * @param body HTTP message body
         * @param contentType HTTP content type
         */
        void SendPostRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType);

        /**
         * Send a PUT request.
         *
         * @param module AwsMock module name
         * @param url HTTP URL
         * @param body HTTP message body
         * @param contentType HTTP content type
         */
        void SendPutRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType);

        /**
         * Send a DELETE request
         *
         * @param module AwsMock module name
         * @param url HTTP URL
         * @param body HTTP message body
         * @param contentType HTTP content type
         */
        void SendDeleteRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType);

        /**
         * Send a HEAD request
         *
         * @param module AwsMock module name
         * @param url HTTP URL
         * @param contentType HTTP content type
         * @return true, if state = 200
         */
        bool SendHeadRequest(const std::string &module, const std::string &url, const std::string &contentType);

        /**
         * Send a lambda create function request.
         *
         * @param module AwsMock module name
         * @param url HTTP URL
         * @param fileName name of the file to send
         * @param headers HTTP header map
         */
        void SendFile(const std::string &module, const std::string &url, const std::string &fileName, const std::map<std::string, std::string> &headers);

      private:

        /**
         * Adds the authorization header.
         *
         * @param module AwsMock module name
         * @param request HTTP request
         */
        void AddAuthorization(const std::string &module, Poco::Net::HTTPRequest &request);

        /**
         * Configuration
         */
        const Core::Configuration &_configuration;

        /**
         * Service database
         */
        std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

        /**
         * lambda database
         */
        std::unique_ptr<Database::LambdaDatabase> _lambdaDatabase;

        /**
         * S3 module
         */
        std::unique_ptr<Service::S3Service> _s3Service;

        /**
         * Lambda module
         */
        std::unique_ptr<Service::LambdaService> _lambdaService;

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
         * Lambda module host
         */
        std::string _lambdaServiceHost;

        /**
         * Lambda module port
         */
        int _lambdaServicePort;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_ABSTRACT_WORKER_H
