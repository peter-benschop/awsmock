//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersInGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListUsersInGroupRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "userPoolId");
            groupName = Core::Bson::BsonUtils::GetStringValue(document, "groupName");
            limit = Core::Bson::BsonUtils::GetIntValue(document, "limit");
            nextToken = Core::Bson::BsonUtils::GetStringValue(document, "nextToken");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListUsersInGroupRequest::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "userPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "groupName", groupName);
            Core::Bson::BsonUtils::SetIntValue(document, "limit", limit);
            Core::Bson::BsonUtils::SetStringValue(document, "nextToken", nextToken);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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