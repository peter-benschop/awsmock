//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWS_MOCK_CORE_DATETIME_UTILS_H
#define AWS_MOCK_CORE_DATETIME_UTILS_H

// C++ standard includes
#include <chrono>
#include <string>

// TZ library includes
#include <date/date.h>

// Boost includes
#include <boost/date_time/posix_time/posix_time_duration.hpp>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/date/tz.h>

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
         * @pre
         * Format is according to ToISO8601, for instance: '2024-04-28T15:07:37.035332Z'.
         *
         * @param timePoint point in time
         * @return time_point in ISO 8601 format
         */
        static std::string ToISO8601(const system_clock::time_point &timePoint);

        /**
         * @brief Returns the current date time in ISO8001 format
         *
         * @pre
         * Format is according to ToISO8601, for instance: '2024-04-28T15:07:37.035332Z'.
         *
         * @return time_point in ISO 8601 format
         */
        static std::string NowISO8601();

        /**
         * @brief Convert a ToISO8601 timestamp into a system time point.
         * @param dateString
         * @return
         */
        static system_clock::time_point FromISO8601(const std::string &dateString);

        /**
         * @brief Returns the current time in HTTP format.
         *
         * @pre
         * Format is according to RFC822, for instance: 'Tue, 15 Nov 2010 08:12:31 +0200'.
         *
         * @return current time in HTTP format
         */
        static std::string HttpFormat();

        /**
         * @brief Returns the time_point in HTTP format
         *
         * @pre
         * Format is according to RFC822, for instance: 'Tue, 15 Nov 2010 08:12:31 +0200'.
         *
         * @param timePoint point in time
         * @return time_point in HTTP format
         */
        static std::string HttpFormat(const system_clock::time_point &timePoint);

        /**
         * @brief Returns the time_point in Unix epoch timestamp (UTC)
         *
         * @param timePoint point in time
         * @return time_point as Unix epoch timestamp
         */
        static long UnixTimestamp(const system_clock::time_point &timePoint);

        /**
         * @brief Returns the time_point in Unix epoch timestamp (LocalTime)
         *
         * @param timePoint point in time
         * @return time_point as Unix epoch timestamp in local time
         */
        static long UnixTimestampLocal(const system_clock::time_point &timePoint);

        /**
         *
         */
        static system_clock::time_point LocalDateTimeNow();
    };

}// namespace AwsMock::Core

#endif//AWS_MOCK_CORE_DATETIME_UTILS_H
