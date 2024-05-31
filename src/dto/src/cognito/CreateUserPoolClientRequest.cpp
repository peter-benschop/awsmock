//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolClientRequest.h>

namespace AwsMock::Dto::Cognito {

    void CreateUserPoolClientRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ClientName", rootObject, clientName);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueBool("GenerateSecret", rootObject, generateSecret);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolClientRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ClientName", clientName);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("GenerateSecret", generateSecret);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolClientRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolClientRequest &r) {
        os << "CreateUserPoolClientRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito