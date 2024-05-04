//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWS_MOCK_CORE_CORE_EXCEPTION_H
#define AWS_MOCK_CORE_CORE_EXCEPTION_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Exception.h>

namespace AwsMock::Core {

    /**
     * Exception class. In case of a COM request failure a COMException is thrown.
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
        explicit CoreException(int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit CoreException(const std::string &msg, int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param arg exception argument, will be appended to the message, separated with a ':'.
         * @param code exception code, default: 0
         */
        CoreException(const std::string &msg, const std::string &arg, int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param exc parent exception.
         * @param code exception code, default: 0
         */
        CoreException(const std::string &msg, const Poco::Exception &exc, int code = 0);

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

        /**
         * Returns the exception class name.
         */
        [[nodiscard]] const char *className() const noexcept override;

        /**
         * Returns a clone of the exception
         */
        [[nodiscard]] Poco::Exception *clone() const override;

        /**
         * Rethrows the exception.
         */
        void rethrow() const override;
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_CORE_EXCEPTION_H
