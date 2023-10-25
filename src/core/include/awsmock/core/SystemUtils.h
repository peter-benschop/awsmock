//
// Created by vogje01 on 12/11/2022.
//

#ifndef AWSMOCK_CORE_SYSTEMUTILS_H_
#define AWSMOCK_CORE_SYSTEMUTILS_H_

// C includes
#include <fcntl.h>
#include <pwd.h>

// C++ includes
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <array>
#include <climits>
#include <unistd.h>
#include <cstdlib>
#include <filesystem>
#include <regex>

// Poco includes
#include <Poco/String.h>
#include <Poco/RegularExpression.h>

// AwsMock includes
#include "awsmock/core/CoreException.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/StreamFilter.h"
#include "awsmock/core/FileUtils.h"

namespace AwsMock::Core {

    struct ExecResult {
      int status = -1;
      std::string output;
    };
    typedef struct ExecResult ExecResult;

    /**
     * System utils for command line execution and other system routines.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class SystemUtils {

    public:

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
       * Logger
       */
      static Core::LogStream _logger;

    };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_SYSTEMUTILS_H_
