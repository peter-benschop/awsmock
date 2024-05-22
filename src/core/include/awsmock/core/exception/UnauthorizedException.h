//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_UNAUTHORIZED_EXCEPTION_H
#define AWSMOCK_CORE_UNAUTHORIZED_EXCEPTION_H

#include "Poco/Exception.h"
#include "Poco/Net/HTTPResponse.h"

namespace AwsMock::Core {

    /**
     * Resource not found exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class UnauthorizedException : public Poco::Exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit UnauthorizedException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_UNAUTHORIZED);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit UnauthorizedException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_UNAUTHORIZED);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        UnauthorizedException(const UnauthorizedException &exc);

        /**
         * Destructor
         */
        ~UnauthorizedException() noexcept override;

        /**
         * Assigment operator.
         */
        UnauthorizedException &operator=(const UnauthorizedException &exc);

        /**
         * Rethrows the exception.
         */
        void rethrow() const;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_UNAUTHORIZED_EXCEPTION_H
