//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVER_GATEWAY_SERVER_H
#define AWSMOCK_SERVER_GATEWAY_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
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
     * @author jens.vogt\@opitz-consulting.com
     */
    class GatewayServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit GatewayServer();

      protected:

        /**
         * @brief Timer initialization
         */
        void Initialize() override;

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Service database
         */
        std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

        /**
         * AWS region
         */
        std::string _region;

        /**
         * Sleeping period in ms
         */
        int _period;

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
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVER_GATEWAY_SERVER_H
