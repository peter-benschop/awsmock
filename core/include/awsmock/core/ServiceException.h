//
// Created by vogje01 on 02/09/2022.
//

#ifndef AWSMOCK_CORE_SERVICEEXCEPTION_H
#define AWSMOCK_CORE_SERVICEEXCEPTION_H

#include "Poco/Exception.h"

namespace AwsMock::Core {

    /**
     * COM exception class. In case of a COM request failure a COMException is thrown.
     */
    class ServiceException : public Poco::Exception {
     public:
        /**
         * Constructor.
         *
         * @param code exception code, default: 0
         */
        explicit ServiceException(int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param code exception code, default: 0
         */
        explicit ServiceException(const std::string &msg, int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param arg exception argument, will be appended to the message, separated with a ':'.
         * @param code exception code, default: 0
         */
        ServiceException(const std::string &msg, const std::string &arg, int code = 0);

        /**
         * Constructor.
         *
         * @param msg exception message
         * @param exc parent exception.
         * @param code exception code, default: 0
         */
        ServiceException(const std::string &msg, const Poco::Exception &exc, int code = 0);

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
      const char *name() const noexcept override;

      /**
       * Returns the exception class name.
       */
      const char *className() const noexcept override;

      /**
       * Returns a clone of the exception
       */
      Poco::Exception *clone() const override;

      /**
       * Rethrows the exception.
       */
      void rethrow() const override;
    };

} // namespace AwsMock::Core

#endif //AWSMOCK_CORE_SERVICEEXCEPTION_H
