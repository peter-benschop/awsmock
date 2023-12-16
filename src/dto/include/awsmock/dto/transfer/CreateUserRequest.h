//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_CREATEUSERREQUEST_H
#define AWSMOCK_DTO_TRANSFER_CREATEUSERREQUEST_H

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

  struct CreateUserRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Server ID
     */
    std::string serverId;

    /**
     * User name
     */
    std::string userName;

    /**
     * Password
     */
    std::string password;

    /**
     * Home directory
     */
    std::string homeDirectory;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const {

      try {
        Poco::JSON::Object rootJson;
        rootJson.set("Region", region);
        rootJson.set("ServerId", serverId);
        rootJson.set("UserName", userName);
        rootJson.set("Password", password);
        rootJson.set("HomeDirectory", homeDirectory);

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

        // Set userAttributes
        Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
        Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);
        Core::JsonUtils::GetJsonValueString("UserName", rootObject, userName);
        Core::JsonUtils::GetJsonValueString("Password", rootObject, password);
        Core::JsonUtils::GetJsonValueString("HomeDirectory", rootObject, homeDirectory);

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
    friend std::ostream &operator<<(std::ostream &os, const CreateUserRequest &r) {
      os << "CreateUserRequest={region='" << r.region << "' serverId='" << r.serverId << "' userName='" << r.userName << "' password:='" << r.password
         << "' homeDirectory='" << r.homeDirectory << "}";
      return os;
    }
  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_TRANSFER_CREATEUSERREQUEST_H
