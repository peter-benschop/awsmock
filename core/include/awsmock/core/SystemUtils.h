//
// Created by vogje01 on 12/11/2022.
//

#ifndef AWSMOCK_CORE_SYSTEMUTILS_H_
#define AWSMOCK_CORE_SYSTEMUTILS_H_

// C++ includes
#include <cstdio>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <climits>
#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <chrono>
#include <pwd.h>
#include <fstream>
#include <filesystem>

// Poco includes
#include <Poco/Logger.h>

// AwsMock includes
#include "awsmock/core/CoreException.h"

namespace AwsMock::Core {

    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

    struct ExecResult {
      int status = -1;
      std::string output;
    };

    /**
     * System utils for command line execution and other system routines.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class SystemUtils {
    public:

      SystemUtils() : _logger(Poco::Logger::get("root")) {}

      /**
       * Execute system command and capture the stdout output result.
       *
       * @param command command string
       * @return command output.
       */
      static ExecResult Exec(const std::string &command);

      /**
       * Returns the current working directory.
       *
       * @return absolute path of the current work directory.
       */
      static std::string GetCurrentWorkingDir();

      /**
       * Returns the home directory of the user
       *
       * @return absolute path of the home directory.
       */
      static std::string GetHomeDir();

      /**
       * Install a signal handler.
       */
      static void InstallSignalHandler();

      /**
       * Start timer
       *
       * @return time point of now()
       */
      static TimePoint StartTimer() {
          return std::chrono::high_resolution_clock::now();
      }

      /**
       * Stop timer
       *
       * @param msg message to print
       * @param startTime start time point
       */
      static void StopTimer(const std::string &msg, TimePoint startTime) {
          std::cerr << msg << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() << "ms"
                    << std::endl;
      }

    private:
      /**
       * Posix signal handler.
       *
       * @param signum signal number.
       */
      static void SignalHandler(int signum);

      /**
       * Logger
       */
      Poco::Logger &_logger;
    };

} // namespace AwsMOck::Core

#endif //AWSMOCK_CORE_SYSTEMUTILS_H_
