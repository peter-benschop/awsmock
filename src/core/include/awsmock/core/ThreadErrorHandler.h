//
// Created by vogje01 on 24/08/2022.
//

#ifndef AWSMOCK_CORE_THREADERRORHANDLER_H
#define AWSMOCK_CORE_THREADERRORHANDLER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/ErrorHandler.h"

// Aws mock includs
#include <awsmock/core/LogStream.h>

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
      log_error << "Unhandled POCO exception: " + exc.displayText() + " in class: " + exc.className();
    }

    /**
     * C++ standard exception.
     *
     * @param exc standard exception
     */
    void exception(const std::exception &exc) override {
      log_error << "Unhandled STD exception: " << std::string(exc.what());
    }

    /**
     * All other exceptions
     */
    void exception() override {
      log_error << "Unknown exception";
    }

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

  };

} // namespace AwsMock::Core

#endif //AWSMOCK_CORE_THREADERRORHANDLER_H
