//
// Created by vogje01 on 6/3/24.
//

#ifndef AWSMOCK_ABSTRACT_DOMAIN_SOCKET_H
#define AWSMOCK_ABSTRACT_DOMAIN_SOCKET_H

// C++ includes
#include <string>

// Boost includes
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace AwsMock::Service {

    using boost::asio::local::stream_protocol;

    /**
     * @brief Abstract domain socket
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class AbstractDomainSocket {

      public:

        /**
         * @brief Constructor
         *
         * @param ioc boost IO context
         * @param socketPath
         */
        explicit AbstractDomainSocket(boost::asio::io_context &ioc, const std::string &socketPath);

        /**
         * @brief Main method
         */
        void Run();

      private:

        /**
         * Socket path
         */
        std::string _socketPath;

        /**
         * Socket acceptor
         */
        stream_protocol::acceptor _acceptor;
    };

}// namespace AwsMock::Service
#endif// AWSMOCK_ABSTRACT_DOMAIN_SOCKET_H
