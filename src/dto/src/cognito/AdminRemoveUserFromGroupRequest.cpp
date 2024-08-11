//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminRemoveUserFromGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    std::string AdminRemoveUserFromGroupRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("GroupName", groupName);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("Username", userName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void AdminRemoveUserFromGroupRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("GroupName", rootObject, groupName);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueString("Username", rootObject, userName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AdminRemoveUserFromGroupRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminRemoveUserFromGroupRequest &r) {
        os << "AdminRemoveUserFromGroupRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito