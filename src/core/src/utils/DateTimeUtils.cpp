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
};

