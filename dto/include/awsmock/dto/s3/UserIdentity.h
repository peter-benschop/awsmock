//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_USERIDENTITY_H
#define AWSMOCK_DTO_S3_USERIDENTITY_H

// C++ standard includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::S3 {

    struct UserIdentity {

      /**
       * AWS principal ID
       */
      std::string principalId;

      /**
       * Converts the DTO to a JSON representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const UserIdentity &r);

    };
}
#endif // AWSMOCK_DTO_S3_USERIDENTITY_H
