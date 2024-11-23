//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/CreateUserRequest.h>

namespace AwsMock::Dto::Transfer {

    std::string CreateUserRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ServerId", serverId);
            rootJson.set("UserName", userName);
            rootJson.set("Password", password);
            rootJson.set("HomeDirectory", homeDirectory);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateUserRequest::FromJson(const std::string &body) {

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
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserRequest &r) {
        os << "CreateUserRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
