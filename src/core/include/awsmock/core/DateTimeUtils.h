//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWS_MOCK_CORE_DATETIME_UTILS_H
#define AWS_MOCK_CORE_DATETIME_UTILS_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Core {

  /**
   * Date time utilities.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class DateTimeUtils {

  public:

    static std::string AwsDatetime(const Poco::DateTime &dateTime);

    static std::string AwsDatetimeNow();

  };
} // namespace AwsMock::Core
#endif //AWS_MOCK_CORE_DATETIME_UTILS_H
