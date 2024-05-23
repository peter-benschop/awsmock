//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_BAD_REQUEST_EXCEPTION_H
#define AWSMOCK_CORE_BAD_REQUEST_EXCEPTION_H

#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>

namespace AwsMock::Core {

    /**
     * @brief Bad request exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class BadRequestException : public Poco::Exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit BadRequestException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit BadRequestException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        BadRequestException(const BadRequestException &exc);

        /**
         * Destructor
         */
        ~BadRequestException() noexcept override;

        /**
         * Assigment operator.
         */
        BadRequestException &operator=(const BadRequestException &exc);

        /**
         * Rethrows the exception.
         */
        void rethrow() const;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_BAD_REQUEST_EXCEPTION_H
