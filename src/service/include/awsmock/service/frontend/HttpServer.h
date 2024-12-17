//
// Created by vogje01 on 12/17/24.
//

#ifndef AWSMOCK_SERVICE_FRONTEND_HTTP_SERVER_H
#define AWSMOCK_SERVICE_FRONTEND_HTTP_SERVER_H

// C++ standard includes
#include <list>
#include <string>

// Boost includes
#include <asio/ip/tcp.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/service/frontend/HttpWorker.h>

namespace AwsMock::Service::Frontend {

    class HttpServer {

      public:

        /**
         * Constructor
         */
        HttpServer() = default;

        /**
       * @brief Executes a lambda function
       */
        void operator()() const;
    };

}// namespace AwsMock::Service::Frontend

#endif// AWSMOCK_SERVICE_FRONTEND_HTTP_SERVER_H
