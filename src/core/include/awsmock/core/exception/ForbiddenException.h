//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_FORBIDDEN_H
#define AWSMOCK_CORE_FORBIDDEN_H

// Boost includes
#include <boost/beast/http/basic_parser.hpp>
#include <boost/beast/http/status.hpp>

namespace AwsMock::Core {

    /**
     * @brief Resource not found exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ForbiddenException final : public std::exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit ForbiddenException(boost::beast::http::status code = boost::beast::http::status::forbidden);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit ForbiddenException(const std::string &msg, boost::beast::http::status code = boost::beast::http::status::forbidden);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        ForbiddenException(const ForbiddenException &exc);

        /**
         * Destructor
         */
        ~ForbiddenException() noexcept override;

        /**
         * Assigment operator.
         */
        ForbiddenException &operator=(const ForbiddenException &exc);

        /**
         * Rethrows the exception.
         */
        void rethrow() const;

      private:

        std::string message;
        boost::beast::http::status code;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_FORBIDDEN_H
