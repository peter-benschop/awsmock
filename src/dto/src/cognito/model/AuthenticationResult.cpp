//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/AuthenticationResult.h>

namespace AwsMock::Dto::Cognito {

    std::string AuthenticationResult::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object AuthenticationResult::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("AccessToken", accessToken);
            rootJson.set("IdToken", idToken);
            rootJson.set("RefreshToken", refreshToken);
            rootJson.set("TokenType", tokenType);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AuthenticationResult::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AuthenticationResult &o) {
        os << "AuthenticationResult=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
