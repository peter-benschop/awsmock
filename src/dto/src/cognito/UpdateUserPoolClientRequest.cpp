//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/UpdateUserPoolClientRequest.h>

namespace AwsMock::Dto::Cognito {

    void UpdateUserPoolClientRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueString("ClientId", rootObject, clientId);
            Core::JsonUtils::GetJsonValueString("ClientName", rootObject, clientName);
            Core::JsonUtils::GetJsonValueInt("AccessTokenValidity", rootObject, accessTokenValidity);
            Core::JsonUtils::GetJsonValueInt("IdTokenValidity", rootObject, idTokenValidity);
            Core::JsonUtils::GetJsonValueInt("RefreshTokenValidity", rootObject, refreshTokenValidity);

            if (rootObject->has("TokenValidityUnits")) {
                tokenValidityUnits.FromJsonObject(rootObject->getObject("TokenValidityUnits"));
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateUserPoolClientRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("ClientId", clientId);
            rootJson.set("ClientName", clientName);
            rootJson.set("AccessTokenValidity", accessTokenValidity);
            rootJson.set("IdTokenValidity", idTokenValidity);
            rootJson.set("RefreshTokenValidity", refreshTokenValidity);
            rootJson.set("TokenValidityUnits", tokenValidityUnits.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateUserPoolClientRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateUserPoolClientRequest &r) {
        os << "UpdateUserPoolClientRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito