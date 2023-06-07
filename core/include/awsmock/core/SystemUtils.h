//
// Created by vogje01 on 12/11/2022.
//

#ifndef AWSMOCK_CORE_SYSTEMUTILS_H_
#define AWSMOCK_CORE_SYSTEMUTILS_H_

// C includes
#include <fcntl.h>
#include <pwd.h>
#include <sys/socket.h>
#include <sys/un.h>

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
#include <Poco/Logger.h>
#include <Poco/String.h>
#include <Poco/RegularExpression.h>

// AwsMock includes
#include "awsmock/core/CoreException.h"

#define CHUNK_SIZE 65536

namespace AwsMock::Core {

    static const unsigned int s_recv_len = 8192;

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
       * Send a file over a UNIX domain socket
       *
       * @param socketPath name of the UNIX domain socket
       * @param header HTTP header to send.
       * @param fileName name of the file to send as body.
       * @return output from socket operation
       */
      static std::string SendFileViaDomainSocket(const char* socketPath, const std::string &header, const std::string &fileName);

      /**
       * Send a message string over a UNIX domain socket
       *
       * @param socketPath name of the UNIX domain socket
       * @param header header string.
       * @param body message body.
       * @return output from socket operation
       */
      static std::string SendMessageViaDomainSocket(const char* socketPath, const std::string &header, const std::string &body);

      /**
       * Set a HTTP header string in the correct format, to be used for a UNIX domain socket connection.
       *
       * @param method
       * @param url
       * @param contentType
       * @param contentLength
       * @return
       */
      static std::string SetHeader(const std::string &method, const std::string &url, const std::string &contentType, long contentLength);

    private:

      /**
       * Extract the body of the message
       *
       * @param body body string
       * @return body string
       */
      static std::string GetBody(const std::string &output);

      /**
       * Logger
       */
      Poco::Logger &_logger;
    };

} // namespace AwsMOck::Core

#endif //AWSMOCK_CORE_SYSTEMUTILS_H_
