//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/dto/cognito/model/User.h>

namespace AwsMock::Dto::Cognito {

    std::string User::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> User::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "userName", userName);
            Core::Bson::BsonUtils::SetStringValue(document, "userPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "userStatus", Database::Entity::Cognito::UserStatusToString(userStatus));
            Core::Bson::BsonUtils::SetBoolValue(document, "enabled", enabled);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void User::FromDocument(const view_or_value<view, value> &document) {

        try {

            region = Core::Bson::BsonUtils::GetStringValue(document, "region");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "userName");
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "userPoolId");
            enabled = Core::Bson::BsonUtils::GetBoolValue(document, "enabled");
            //userStatus = Database::Entity::Cognito::UserStatusFromString(Core::Bson::BsonUtils::GetStringValue(document, "userStatus"));

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &u) {
        os << "User=" << u.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito