//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/UserPoolClient.h>

namespace AwsMock::Dto::Cognito {

    std::string UserPoolClient::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> UserPoolClient::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientId", clientId);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientName", clientName);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientSecret", clientSecret);
            Core::Bson::BsonUtils::SetDateValue(document, "CreationDate", created);
            Core::Bson::BsonUtils::SetDateValue(document, "LastModified", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UserPoolClient::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserPoolClient &o) {
        os << "UserPoolClient=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
