//
// Created by vogje01 on 05/01/2023.
//

#ifndef AWSMOCK_CORE_LOGGER_H
#define AWSMOCK_CORE_LOGGER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>

// AwsMock includes
#include <awsmock/core/JsonLogFormatter.h>

namespace AwsMock::Core {

    /**
     * Logger used to generate JSON output and text logging output to the console.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class Logger {
    public:
      /**
       * Default constructor
       */
      Logger();

      /**
       * Constructor.
       *
       * @param profile profile to use.
       */
      explicit Logger(const std::string &profile);

      /**
       * Set environment.
       *
       * For a 'localstack' profile a console logger is used, otherwise a JSON console logger will be implemented.
       *
       * @param profile profile to set
       */
      static void SetProfile(const std::string &profile);

      /**
       * Set log level.
       *
       * @param logLevel logging level to set
       */
      static void SetLogLevel(const std::string &logLevel);

      /**
       * Configures the default console logger.
       */
      static void SetDefaultConsoleLogger();

      /**
       * Configures the default console logger.
       *
       * @param loggerName name oof the logger
       */
      static void SetDefaultConsoleLogger(const std::string &loggerName);

      /**
       * Configures the JSON console logger.
       */
      static void SetJsonConsoleLogger();

    private:

      /**
       * Default log pattern
       */
      static const std::string DEFAULT_LOG_PATTERN;

    };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_LOGGER_H
