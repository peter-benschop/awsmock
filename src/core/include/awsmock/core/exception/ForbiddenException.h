//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_FORBIDDEN_H
#define AWSMOCK_CORE_FORBIDDEN_H

#include "Poco/Exception.h"
#include "Poco/Net/HTTPResponse.h"

namespace AwsMock::Core {

    /**
     * @brief Resource not found exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ForbiddenException : public Poco::Exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit ForbiddenException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_FORBIDDEN);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit ForbiddenException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_FORBIDDEN);

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
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_FORBIDDEN_H
