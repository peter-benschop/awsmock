//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/AuthenticationResult.h>

namespace AwsMock::Dto::Cognito {

    std::string AuthenticationResult::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> AuthenticationResult::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "AccessToken", accessToken);
            Core::Bson::BsonUtils::SetStringValue(document, "IdToken", idToken);
            Core::Bson::BsonUtils::SetStringValue(document, "RefreshToken", refreshToken);
            Core::Bson::BsonUtils::SetStringValue(document, "TokenType", tokenType);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AuthenticationResult::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AuthenticationResult &o) {
        os << "AuthenticationResult=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
