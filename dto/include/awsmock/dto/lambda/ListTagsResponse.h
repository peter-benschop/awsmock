//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H
#define AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Dto::Lambda {

    struct ListTagsResponse {

      /**
       * Tags
       */
      std::map<std::string, std::string> tags;

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      [[nodiscard]] std::string ToJson() {

          try {
              Poco::JSON::Object rootJson;
              Poco::JSON::Object tagsObject;
              for (const auto &t : tags) {
                  tagsObject.set(t.first, t.second);
              }
              rootJson.set("Tags", tagsObject);

              std::ostringstream os;
              rootJson.stringify(os);
              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
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
      friend std::ostream &operator<<(std::ostream &os, const ListTagsResponse &r) {
          os << "ListTagsResponse={[";
          for (const auto &t : r.tags) {
              os << "key='" << t.first << "' value='" << t.second << "'";
          }
          os << "]}";
          return os;
      }
    };

} // namespace AwsMock::Dto::Lambda

#endif // AWSMOCK_DTO_LAMBDA_LISTTAGSREQUEST_H
