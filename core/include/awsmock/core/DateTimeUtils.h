//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DATETIMEUTILS_H
#define AWSMOCK_CORE_DATETIMEUTILS_H

// C++ standard includes
#include <string>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

namespace AwsMock::Core {

    class DateTimeUtils {
    public:

      static std::string AwsDatetime(const Poco::DateTime& dateTime);

      static std::string AwsDatetimeNow();

    };
} // namespace AwsMock::Core
#endif //AWSMOCK_CORE_DATETIMEUTILS_H
