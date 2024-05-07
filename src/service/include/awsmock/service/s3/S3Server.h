//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVER_H
#define AWSMOCK_SERVICE_S3_SERVER_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/core/Timer.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/s3/S3HandlerFactory.h>
#include <awsmock/service/s3/S3Monitoring.h>

#define S3_DEFAULT_PORT 9500
#define S3_DEFAULT_HOST "localhost"
#define S3_DEFAULT_QUEUE_SIZE 250
#define S3_DEFAULT_MAX_THREADS 50
#define S3_DEFAULT_TIMEOUT 900
#define S3_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * S3 HTTP server
     *
     * <p>
     * The S3 HTTP server gates the requests from the gateway, which acts like a API gateway. The S3 default port is 9500 and can set in the AwsMOck configuration file
     * <i>/etc/awsmock.properties</i>
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Server : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit S3Server(Core::Configuration &configuration);

        /**
         * Timer initialization
         */
        void Initialize() override;

        /**
         * Timer main method
         */
        void Run() override;

        /**
         * Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Rest port
         */
        int _port;

        /**
         * Rest host
         */
        std::string _host;

        /**
        * Application configuration
        */
        Core::Configuration &_configuration;

        /**
         * HTTP manager instance
         */
        std::shared_ptr<Poco::Net::HTTPServer> _httpServer;

        /**
         * S3 monitoring
         */
        std::shared_ptr<S3Monitoring> _s3Monitoring;

        /**
         * HTTP max message queue length
         */
        int _maxQueueLength;

        /**
         * HTTP max concurrent connection
         */
        int _maxThreads;

        /**
         * HTTP request timeout in seconds
         */
        int _requestTimeout;

        /**
         * Data directory
         */
        std::string _dataDir;

        /**
         * Module name
         */
        std::string _module;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_SERVER_H
