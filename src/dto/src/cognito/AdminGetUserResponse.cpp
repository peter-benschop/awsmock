//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminGetUserResponse.h>

namespace AwsMock::Dto::Cognito {

    void AdminGetUserResponse::FromJson(const std::string &payload) {

        try {

            const value document = bsoncxx::from_json(payload);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            userName = Core::Bson::BsonUtils::GetStringValue(document, "Username");

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

    std::string AdminGetUserResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Username", userName);
            rootJson.set("Enabled", enabled);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AdminGetUserResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminGetUserResponse &r) {
        os << "AdminGetUserResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito