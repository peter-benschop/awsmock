//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVER_GATEWAY_SERVER_H
#define AWSMOCK_SERVER_GATEWAY_SERVER_H

// C++ standard includes
#include <string>

// Boost includes
#include <boost/asio/io_service.hpp>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/lambda/model/InvocationNotification.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/gateway/GatewayListener.h>
#include <awsmock/service/lambda/LambdaCreator.h>
#include <awsmock/service/lambda/LambdaExecutor.h>
#include <awsmock/service/s3/S3Service.h>

#define GATEWAY_DEFAULT_HOST "localhost"
#define GATEWAY_DEFAULT_ADDRESS "0.0.0.0"
#define GATEWAY_MAX_QUEUE 250
#define GATEWAY_MAX_THREADS 50
#define GATEWAY_TIMEOUT 900

namespace AwsMock::Service {

    namespace ip = boost::asio::ip;

    /**
     * @brief Gateway server
     *
     * The Gateway server acting as API gateway for the different AWS services. Per default it runs on port 4566. In order to use a different port, set the port in the
     * ```awsmock.properties``` file. The gateway has an internal routing table for the different AWS modules. Each module runs ona different port starting with 9500. Per
     * default the server runs with 50 threads, which means 50 connection can be handled simultaneously. If you need more concurrent connection set the
     * ```awsmock.service.gateway.http.max.threads``` in the properties file.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class GatewayServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit GatewayServer(boost::asio::thread_pool &pool);

        /**
         * @brief Timer initialization
         */
        void Initialize() override;

        /**
         * @brief Start
         */
        void Start() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * Service database
         */
        std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

        /**
         * Rest port
         */
        unsigned short _port;

        /**
         * Rest host
         */
        std::string _host;

        /**
         * HTTP address
         */
        std::string _address;

        /**
         * HTTP max message queue length
         */
        int _maxQueueLength;

        /**
         * HTTP max concurrent connection
         */
        int _maxThreads;

        /**
         * HTTP request timeout
         */
        int _requestTimeout;

        /**
         * Thread pool
         */
        std::vector<std::thread> _threads;
        boost::thread_group _threadGroup;

        boost::asio::thread_pool &_pool;

        boost::asio::io_context ioc{10};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVER_GATEWAY_SERVER_H
