//
// Created by vogje01 on 24/08/2022.
//

#ifndef AWSMOCK_CORE_THREADERRORHANDLER_H
#define AWSMOCK_CORE_THREADERRORHANDLER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/ErrorHandler.h"

namespace AwsMock::Core {

    /**
     * Handles unmatched exception.
     *
     * <p>They will be only logged, for investigation.</p>
     */
    class ThreadErrorHandler : public Poco::ErrorHandler {

    public:

      ThreadErrorHandler() : _logger(Poco::Logger::get("root")) {}

      /**
       * Poco exceptions.
       *
       * @param exc poco exception
       */
      void exception(const Poco::Exception &exc) override {
          poco_error(_logger, "Unhandled POCO exception: " + exc.displayText() + " in class: " + exc.className());
      }

      /**
       * C++ standard exception.
       *
       * @param exc standard exception
       */
      void exception(const std::exception &exc) override {
          poco_error(_logger, "Unhandled STD exception: " + std::string(exc.what()));
      }

      /**
       * All other exceptions
       */
      void exception() override {
          poco_error(_logger, "Unknown exception");
      }

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Core

#endif //AWSMOCK_CORE_THREADERRORHANDLER_H
