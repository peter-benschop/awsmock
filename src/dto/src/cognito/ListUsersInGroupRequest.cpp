//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersInGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListUsersInGroupRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueString("GroupName", rootObject, groupName);
            Core::JsonUtils::GetJsonValueInt("Limit", rootObject, limit);
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUsersInGroupRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("GroupName", groupName);
            rootJson.set("Limit", limit);
            rootJson.set("NextToken", nextToken);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUsersInGroupRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersInGroupRequest &r) {
        os << "ListUsersInGroupRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito