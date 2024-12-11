//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolClientRequest.h>

namespace AwsMock::Dto::Cognito {

    void CreateUserPoolClientRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            clientName = Core::Bson::BsonUtils::GetStringValue(document, "ClientName");
            userPoolId = Core::Bson::BsonUtils::GetStringValue(document, "UserPoolId");
            generateSecret = Core::Bson::BsonUtils::GetBoolValue(document, "GenerateSecret");

            if (document.view().find("TokenValidityUnits") != document.view().end()) {
                tokenValidityUnits.FromDocument(document.view()["TokenValidityUnits"].get_document().value);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateUserPoolClientRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientName", clientName);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetBoolValue(document, "GenerateSecret", generateSecret);

            document.append(kvp("TokenValidityUnits", tokenValidityUnits.ToDocument()));

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateUserPoolClientRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolClientRequest &r) {
        os << "CreateUserPoolClientRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito