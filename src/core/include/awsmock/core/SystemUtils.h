//
// Created by vogje01 on 12/11/2022.
//

#ifndef AWSMOCK_CORE_SYSTEM_UTILS_H
#define AWSMOCK_CORE_SYSTEM_UTILS_H

// C includes
#include <fcntl.h>
#ifndef _WIN32
#include <pwd.h>
#include <unistd.h>
#endif

// C++ includes
#include <array>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#endif

// Poco includes
#include <Poco/Environment.h>
#include <Poco/RegularExpression.h>
#include <Poco/String.h>

// AwsMock includes
#include <awsmock/core/CoreException.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/RandomUtils.h>
#include <awsmock/core/StreamFilter.h>

#define RANDOM_PORT_MIN 32768
#define RANDOM_PORT_MAX 65536

namespace AwsMock::Core {

    struct ExecResult {
        int status = -1;
        std::string output;
    };
    typedef struct ExecResult ExecResult;

    /**
     * System utils for command line execution and other system routines.
     *
     * @author jens.vogt\@opitz-consulting.com
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
         * Returns the node name (uname -n) of the server
         *
         * @return node name of the server
         */
        static std::string GetNodeName();

        /**
         * Returns the DNS host name of the server
         *
         * @return host name of the server
         */
        static std::string GetHostName();

        /**
         * Returns a random port number between 32768 and 65536
         *
         * @return random port
         */
        static int GetRandomPort();
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_SYSTEM_UTILS_H
