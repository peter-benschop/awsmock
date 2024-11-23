//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/SignUpRequest.h>

namespace AwsMock::Dto::Cognito {

    void SignUpRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ClientId", rootObject, clientId);
            Core::JsonUtils::GetJsonValueString("Username", rootObject, userName);
            Core::JsonUtils::GetJsonValueString("Password", rootObject, password);
            Core::JsonUtils::GetJsonValueString("SecretHash", rootObject, secretHash);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SignUpRequest::ToJson() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ClientId", clientId);
            rootJson.set("Username", userName);
            rootJson.set("Password", password);
            rootJson.set("SecretHash", secretHash);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SignUpRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SignUpRequest &r) {
        os << "SignUpRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito