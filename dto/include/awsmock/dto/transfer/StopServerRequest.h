//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_STOPSERVERREQUEST_H
#define AWSMOCK_DTO_TRANSFER_STOPSERVERREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::Transfer {

    struct StopServerRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Maximal number of results
       */
      std::string serverId;

      /**
       * Parse a JSON stream
       *
       * @param body json input stream
       */
      void FromJson(const std::string &body) {

          Poco::JSON::Parser parser;
          Poco::Dynamic::Var result = parser.parse(body);
          Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

          try {

              // Get root values
              Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
              Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const StopServerRequest &r) {
          os << "StopServerRequest={region='" << r.region << "' serverId='" << r.serverId << "'}";
          return os;
      }
    };

} // namespace AwsMock::Dto::Lambda

#endif // AWSMOCK_DTO_TRANSFER_STOPSERVERREQUEST_H
