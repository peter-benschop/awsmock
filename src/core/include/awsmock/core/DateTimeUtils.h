//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWS_MOCK_CORE_DATETIME_UTILS_H
#define AWS_MOCK_CORE_DATETIME_UTILS_H

// C++ standard includes
#include <chrono>
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Core {

    using std::chrono::system_clock;

    /**
     * @brief Date time utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DateTimeUtils {

      public:

        /**
         * @brief AWS date time
         *
         * @param dateTime date time
         * @return AWS date time format
         */
        static std::string AwsDatetime(const Poco::DateTime &dateTime);

        /**
         * @brief Current date time in AWS format
         *
         * @return current time in AWS date time format
         */
        static std::string AwsDatetimeNow();

        /**
         * @brief Returns the time_point in ISO8001 format
         *
         * ISO8601 is '2024-04-28T15:07:37.035332Z'.
         *
         * @return time_point in ISO 8601 format
         */
        static std::string ISO8601(const system_clock::time_point &timePoint);

        /**
         * @brief Returns the current date time in ISO8001 format
         *
         * ISO8601 is '2024-04-28T15:07:37.035332Z'.
         *
         * @return time_point in ISO 8601 format
         */
        static std::string ISO8601Now();

        /**
         * @brief Returns the time_point in HTTP format
         *
         * HTTP format is 'Tue, 15 Nov 2010 08:12:31 GMT'.
         *
         * @return time_point in HTTP format
         */
        static std::string HttpFormat(const system_clock::time_point &timePoint);
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_DATETIME_UTILS_H
