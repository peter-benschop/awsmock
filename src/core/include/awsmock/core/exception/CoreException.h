//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWS_MOCK_CORE_CORE_EXCEPTION_H
#define AWS_MOCK_CORE_CORE_EXCEPTION_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>

namespace AwsMock::Core {

    /**
     * @brief Exception class. In case of a COM request failure a COMException is thrown.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CoreException : public Poco::Exception {
      public:

        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit CoreException(int code = Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit CoreException(const std::string &msg, int code = Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param arg exception argument, will be appended to the message, separated with a ':'.
         * @param code exception code, default: 0
         */
        CoreException(const std::string &msg, const std::string &arg, int code = Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param exc parent exception.
         * @param code exception code, default: 0
         */
        CoreException(const std::string &msg, const Poco::Exception &exc, int code = Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        /**
         * Copy constructor.
         *
         * @param exc parent exception.
         */
        CoreException(const CoreException &exc);

        /**
         * Destructor
         */
        ~CoreException() noexcept override;

        /**
         * Assigment operator.
         */
        CoreException &operator=(const CoreException &exc);

        /**
         * Returns the exception name.
         */
        [[nodiscard]] const char *name() const noexcept override;

#ifndef _WIN32
        /**
         * Returns the exception class name.
         */
        [[nodiscard]] const char *className() const noexcept override;
#endif
        /**
         * Returns a clone of the exception
         */
        [[nodiscard]] Core::CoreException *clone() const override;

        /**
         * Rethrows the exception.
         */
        void rethrow() const override;
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_CORE_EXCEPTION_H
