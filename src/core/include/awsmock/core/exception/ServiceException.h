//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_SERVICE_EXCEPTION_H
#define AWSMOCK_CORE_SERVICE_EXCEPTION_H

// Poco includes
#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace AwsMock::Core {

    /**
     * @brief Service exception class. In case of a request failure a ServiceException is thrown.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ServiceException : public Poco::Exception {

      public:

        /**
         * @brief Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit ServiceException(int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
         *@brief  Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit ServiceException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * @brief Constructor.
         *
         * @param msg exception message
         * @param arg exception argument, will be appended to the message, separated with a ':'.
         * @param code exception code, default: 0
         */
        ServiceException(const std::string &msg, const std::string &arg, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * @brief Constructor.
         *
         * @param msg exception message
         * @param exc parent exception.
         * @param code exception code, default: 0
         */
        ServiceException(const std::string &msg, const Poco::Exception &exc, int code = Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * @brief Copy constructor.
         *
         * @param exc parent exception.
         */
        ServiceException(const ServiceException &exc);

        /**
         * @brief Destructor
         */
        ~ServiceException() noexcept override;

        /**
         * @brief Assigment operator.
         *
         * @return service exception
         */
        ServiceException &operator=(const ServiceException &exc);

        /**
         * @brief Returns the exception name.
         *
         * @return name of the exception
         */
        [[nodiscard]] const char *name() const noexcept override;

        /**
         * @brief Returns the exception class name.
         *
         * @return class name
         */
        [[nodiscard]] const char *className() const noexcept override;

        /**
         * @brief Returns a clone of the exception
         *
         * @return clone of the exception
         */
        [[nodiscard]] Poco::Exception *clone() const override;

        /**
         * @brief Rethrows the exception.
         */
        void rethrow() const override;
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_SERVICE_EXCEPTION_H
