//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/core/DateTimeUtils.h>

namespace AwsMock::Core {

    std::string DateTimeUtils::AwsDatetime(const Poco::DateTime &dateTime) {
        return Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT);
    }

    std::string DateTimeUtils::AwsDatetimeNow() {
        Poco::DateTime now;
        return Poco::DateTimeFormatter::format(now, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT);
    }

    std::string DateTimeUtils::ToISO8601(const system_clock::time_point &timePoint) {
        return std::format("{:%FT%T}", timePoint);
    }

    std::string DateTimeUtils::NowISO8601() {
        return std::format("{:%FT%TZ}", system_clock::now());
    }

    system_clock::time_point DateTimeUtils::FromISO8601(const std::string &dateString) {
        std::tm t = {};
        // F: Equivalent to %Y-%m-%d, the ISO 8601 date format.
        // T: ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
        // z: ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100). If timezone cannot be determined, no characters
        strptime(dateString.c_str(), "%FT%T", &t);
        t.tm_hour = t.tm_hour + 1;
        return std::chrono::system_clock::from_time_t(mktime(&t));
    }

    std::string DateTimeUtils::HttpFormat() {
        char buf[256];
        time_t timeT = system_clock::to_time_t(system_clock::now());
        struct tm tm = *gmtime(&timeT);
        strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %z", &tm);
        return {buf};
    }

    std::string DateTimeUtils::HttpFormat(const system_clock::time_point &timePoint) {
        char buf[256];
        time_t timeT = system_clock::to_time_t(timePoint);
        struct tm tm = *gmtime(&timeT);
        strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %z", &tm);
        return {buf};
    }

    long DateTimeUtils::UnixTimestamp(const system_clock::time_point &timePoint) {
        return std::chrono::duration_cast<std::chrono::seconds>(timePoint.time_since_epoch()).count();
    }

    long DateTimeUtils::UnixTimestampLocal(const system_clock::time_point &timePoint) {
        return std::chrono::duration_cast<std::chrono::seconds>(date::make_zoned(date::current_zone(), timePoint).get_local_time().time_since_epoch()).count();
    }

    system_clock::time_point DateTimeUtils::LocalDateTimeNow() {
        return system_clock::time_point(date::make_zoned(date::current_zone(), system_clock::now()).get_local_time().time_since_epoch());
    }

};// namespace AwsMock::Core
