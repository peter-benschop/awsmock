//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_NOT_FOUND_EXCEPTION_H
#define AWSMOCK_CORE_NOT_FOUND_EXCEPTION_H

#include "Poco/Exception.h"
#include "Poco/Net/HTTPResponse.h"

namespace AwsMock::Core {

    /**
     * Resource not found exception class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class NotFoundException : public Poco::Exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit NotFoundException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit NotFoundException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        NotFoundException(const NotFoundException &exc);

        /**
         * Destructor
         */
        ~NotFoundException() noexcept override;

        /**
         * Assigment operator.
         */
        NotFoundException &operator=(const NotFoundException &exc);

        /**
         * Rethrows the exception.
         */
        void rethrow() const;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_NOT_FOUND_EXCEPTION_H
