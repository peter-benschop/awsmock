//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_SERVICEEXCEPTION_H
#define AWSMOCK_CORE_SERVICEEXCEPTION_H

// Poco includes
#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace AwsMock::Core {

    /**
     * COM exception class. In case of a COM request failure a COMException is thrown.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class ServiceException : public Poco::Exception {

      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         * @param resource exception resource
         * @param requestId exception resource ID
         */
        explicit ServiceException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR,
                                  const char *resource = nullptr,
                                  const char *requestId = nullptr);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         * @param resource exception resource
         * @param requestId exception resource ID
         */
        explicit ServiceException(const std::string &msg,
                                  int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR,
                                  const char *resource = nullptr,
                                  const char *requestId = nullptr);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param arg exception argument, will be appended to the message, separated with a ':'.
         * @param code exception code, default: 0
         * @param resource exception resource
         * @param requestId exception resource ID
         */
        ServiceException(const std::string &msg,
                         const std::string &arg,
                         int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR,
                         const char *resource = nullptr,
                         const char *requestId = nullptr);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param exc parent exception.
         * @param code exception code, default: 0
         * @param resource exception resource
         * @param requestId exception resource ID
         */
        ServiceException(const std::string &msg,
                         const Poco::Exception &exc,
                         int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR,
                         const char *resource = nullptr,
                         const char *requestId = nullptr);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        ServiceException(const ServiceException &exc);

        /**
         * Destructor
         */
        ~ServiceException() noexcept override;

        /**
         * Assigment operator.
         */
        ServiceException &operator=(const ServiceException &exc);

        /**
         * Returns the exception name.
         */
        [[nodiscard]] const char *name() const noexcept override;

        /**
         * Returns the exception class name.
         */
        [[nodiscard]] const char *className() const noexcept override;

        /**
         * Returns the exception resource.
         */
        [[nodiscard]] const char *resource() const noexcept;

        /**
         * Returns the exception request ID.
         */
        [[nodiscard]] const char *requestId() const noexcept;

        /**
         * Returns a clone of the exception
         */
        [[nodiscard]] Poco::Exception *clone() const override;

        /**
         * Rethrows the exception.
         */
        void rethrow() const override;

      private:

        /**
         * Resource
         */
        const char *_resource;

        /**
         * Request ID
         */
        const char *_requestId;
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_SERVICEEXCEPTION_H
