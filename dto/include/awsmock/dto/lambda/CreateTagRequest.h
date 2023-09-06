//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H
#define AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <utility>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/dto/lambda/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    struct CreateTagRequest {

      /**
       * ARN
       */
      std::string arn;

      /**
       * Tags
       */
      std::map<std::string, std::string> tags;

      /**
       * Constructor
       */
      CreateTagRequest(std::string arn, const std::string &body) : arn(std::move(arn)) {
          FromJson(body);
      }

      /**
       * Convert from a JSON object.
       *
       * @param jsonObject json object
       */
      void FromJson(const std::string &body) {

          try {
              Poco::JSON::Parser parser;
              Poco::Dynamic::Var result = parser.parse(body);
              Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

              Poco::JSON::Object::Ptr tagsObject = rootObject->getObject("Tags");

              Poco::JSON::Object::NameList nameList = tagsObject->getNames();
              for (const auto &name : nameList) {
                  tags[name] = tagsObject->get(name).convert<std::string>();
              }

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Creates a JSON string from the object.
       *
       * @return JSON string
       */
      [[nodiscard]] std::string ToJson() const {

          try {
              Poco::JSON::Object rootObject;

              Poco::JSON::Object tagsJson;
              for (const auto &tag : tags) {
                  tagsJson.set(tag.first, tag.second);
              }

              rootObject.set("Tags", tagsJson);
              std::ostringstream os;
              rootObject.stringify(os);
              return os.str();

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
      friend std::ostream &operator<<(std::ostream &os, const CreateTagRequest &r) {
          os << "CreateTagRequest={tags='[";
          for (const auto &it : r.tags) {
              os << " key: '" << it.first << "' value='" << it.second << "'";
          }
          os << "]}";
          return os;
      }

    };

} // namespace AwsMock::Dto::Lambda

#endif // AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H
