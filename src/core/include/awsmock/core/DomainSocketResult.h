//
// Created by vogje01 on 5/28/24.
//

#ifndef AWSMOCK_CORE_DOMAIN_SOCKET_RESULT_H
#define AWSMOCK_CORE_DOMAIN_SOCKET_RESULT_H

// C++ includes
#include <string>

// Boost includes
#include <boost/beast.hpp>

namespace AwsMock::Core {

    struct DomainSocketResult {

        /**
         * Status code
         */
        boost::beast::http::status statusCode;

        /**
          * Body
          */
        std::string body;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_DOMAIN_SOCKET_RESULT_H
