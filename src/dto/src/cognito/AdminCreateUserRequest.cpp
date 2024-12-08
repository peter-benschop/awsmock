//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminCreateUserRequest.h>

namespace AwsMock::Dto::Cognito {

    std::string AdminCreateUserRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "Username", userName);
            Core::Bson::BsonUtils::SetStringValue(document, "TemporaryPassword", temporaryPassword);

            return Core::Bson ::BsonUtils::ToJsonString(document);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void AdminCreateUserRequest::FromJson(const std::string &payload) {

        try {

            const value document = bsoncxx::from_json(payload);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "UserPoolId");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "Username");
            temporaryPassword = Core::Bson::BsonUtils::GetStringValue(document, "TemporaryPassword");
            messageAction = MessageActionFromString(Core::Bson::BsonUtils::GetStringValue(document, "MessageAction"));

            // Message action
            if (document.find("UserAttributes") != document.end()) {
                array array;
                for (const auto &element: document["UserAttributes"].get_array().value) {
                    UserAttribute userAttribute;
                    userAttribute.FromDocument(element.get_document());
                    userAttributes.emplace_back(userAttribute);
                }
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AdminCreateUserRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminCreateUserRequest &r) {
        os << "AdminCreateUserRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito