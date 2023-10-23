//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_CREATETRANSFERREQUEST_H
#define AWSMOCK_DTO_TRANSFER_CREATETRANSFERREQUEST_H

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
#include <awsmock/dto/lambda/CreateFunctionResponse.h>

namespace AwsMock::Dto::Transfer {

    struct Tag {
      /**
       * Key
       */
      std::string key;

      /**
       * Value
       */
      std::string value;

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
      friend std::ostream &operator<<(std::ostream &os, const Tag &r) {
          os << "Tag={key='" << r.key << "' value='" << r.value << "}";
          return os;
      }
    };

    struct CreateTransferRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Protocols
       */
      std::vector<std::string> protocols = {"ftp"};

      /**
       * Tags
       */
      std::vector<Tag> tags;

      /**
       * Creates a JSON string from the object.
       *
       * @return JSON string
       */
      [[nodiscard]] std::string ToJson() const {

          try {
              Poco::JSON::Object rootJson;
              rootJson.set("region", region);

              std::ostringstream os;
              rootJson.stringify(os);
              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

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
              Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
              Poco::JSON::Array::Ptr protocolsArray = rootObject->getArray("Protocols");
              if (protocolsArray != nullptr) {
                  for (const auto &protocol : *protocolsArray) {
                      protocols.push_back(protocol.convert<std::string>());
                  }
              }

              // Cleanup
              rootObject->clear();
              parser.reset();

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
      friend std::ostream &operator<<(std::ostream &os, const CreateTransferRequest &r) {
          os << "CreateTransferRequest={region='" << r.region << "' {";
          for(const auto &tag : r.tags) {
              os << tag.ToString();
          }
          os << "}";
          return os;
      }
    };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_TRANSFER_CREATETRANSFERREQUEST_H
