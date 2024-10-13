//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_LOG_FORMATTER_H
#define AWSMOCK_LOG_FORMATTER_H

// C++ includes
#include <iomanip>

// PLog includes
#include <plog/Record.h>
#include <plog/Util.h>

namespace AwsMock::Core {

    /**
     * @brief Log pattern formatter.
     *
     * @par
     * The log message will have the following format "Timestamp Severity [ThreadID] [namespace::class::method:lineNo] message.
     *
     * @par Example:
     * @code{.cpp}
     * 2024-05-10 14:38:53.933 WARN  [1255973] [Service::DockerService::GetFirstContainerByImageName:146] Get docker container by name failed, state: 0
     * 2024-05-10 14:38:53.933 DEBUG [1255973] [Core::CurlUtils::SendUnixSocketRequest:47] Request send to docker daemon, state: 301 socket: /var/run/docker.sock
     * 2024-05-10 14:38:53.933 DEBUG [1255973] [Service::DockerService::StartDockerContainer:248] Sending StartServer container request
     * 2024-05-10 14:38:53.933 WARN  [1255973] [Service::DockerService::StartDockerContainer:252] Start container failed, state: 0
     * 2024-05-10 14:38:53.933 INFO  [1255973] [Service::DynamoDbServer::StartLocalDynamoDb:87] Docker containers for DynamoDB started
     * 2024-05-10 14:38:53.933 DEBUG [1255973] [Core::Timer::Start:16] Timer starting, name: dynamodb timeout: 10
     * @endcode
     *
     * @see plog::Formatters/TxtFormatter.h
     * @author jens.vogt\@opitz-consulting.com
     */
    class LogFormatter {

      public:

        /**
         * @brief Writes the file header.
         *
         * @par
         * AwsMock does not use file headers.
         *
         * @return header string
         */
        static plog::util::nstring header() {
            return {};
        }

        /**
         * @brief Format the log record.
         *
         * @param record log record as recorded by plog.
         *
         * @return formatted log message string.
         */
        static plog::util::nstring format(const plog::Record &record) {
            tm t{};
            plog::util::localtime_s(&t, &record.getTime().time);

            plog::util::nostringstream ss;
            ss << t.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".") << std::setfill(PLOG_NSTR('0')) << std::setw(3) << static_cast<int>(record.getTime().millitm) << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
            ss << PLOG_NSTR("[") << record.getTid() << PLOG_NSTR("] ");
            ss << PLOG_NSTR("[") << Remove(record.getFunc()) << PLOG_NSTR(":") << record.getLine() << PLOG_NSTR("] ");
            ss << record.getMessage() << PLOG_NSTR("\n");

            return ss.str();
        }

      private:

        /**
         * @brief Remove the main namespace 'AwsMock'
         *
         * @param func function string from plog record.
         * @return converted string.
         */
        static char *Remove(const char *func) {
            return RemoveStr(func, "AwsMock::");
        }

        /**
         * @brief Remove a string from a string.
         *
         * @param input input string
         * @param toRemove string to be removed
         * @return converted string.
         */
        static char *RemoveStr(const char *input, const char *toRemove) {
            char *chop, *src;
            char *dst = const_cast<char *>(input);
            if (nullptr == (dst = strstr(dst, toRemove)))
                return {};
            size_t length = strlen(toRemove);
            src = dst + length;
            char *end = src + strlen(src);
            while ((chop = strstr(src, toRemove))) {
                memmove(dst, src, chop - src + 1);
                dst += chop - src;
                src = chop + length;
            }
            if (src < end) {
                memmove(dst, src, end - src + 1);
            }
            return dst;
        }
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_LOG_FORMATTER_H
