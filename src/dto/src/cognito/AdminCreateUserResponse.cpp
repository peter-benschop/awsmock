//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminCreateUserResponse.h>

namespace AwsMock::Dto::Cognito {

    void AdminCreateUserResponse::FromJson(const std::string &payload) {

        try {

            const value document = bsoncxx::from_json(payload);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "Username");

            // User attributes
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

    std::string AdminCreateUserResponse::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Username", userName);
            Core::Bson::BsonUtils::SetBoolValue(document, "Enabled", enabled);

            return Core::Bson ::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AdminCreateUserResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminCreateUserResponse &r) {
        os << "AdminCreateUserResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito