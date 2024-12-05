//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminAddUserToGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    std::string AdminAddUserToGroupRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "GroupName", region);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Username", region);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void AdminAddUserToGroupRequest::FromJson(const std::string &payload) {

        try {

            const value document = bsoncxx::from_json(payload);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            groupName = Core::Bson::BsonUtils::GetStringValue(document, "GroupName");
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "UserPoolId");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "Username");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AdminAddUserToGroupRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminAddUserToGroupRequest &r) {
        os << "AdminAddUserToGroupRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito