//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    void CreateGroupRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("GroupName", rootObject, groupName);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueInt("Precedence", rootObject, precedence);
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
            Core::JsonUtils::GetJsonValueString("RoleArn", rootObject, roleArn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateGroupRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("GroupName", groupName);
            rootJson.set("Description", description);
            rootJson.set("Precedence", precedence);
            rootJson.set("RoleArn", roleArn);
            rootJson.set("UserPoolId", userPoolId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateGroupRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateGroupRequest &r) {
        os << "CreateGroupRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito