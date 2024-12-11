//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminDisableUserRequest.h>

namespace AwsMock::Dto::Cognito {

    std::string AdminDisableUserRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "Username", userName);

            return Core::Bson ::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void AdminDisableUserRequest::FromJson(const std::string &payload) {

        try {

            const value document = bsoncxx::from_json(payload);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "UserPoolId");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "Username");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AdminDisableUserRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminDisableUserRequest &r) {
        os << "AdminDisableUserRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito