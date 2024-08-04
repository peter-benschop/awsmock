//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolDomainRequest.h>

namespace AwsMock::Dto::Cognito {

    void CreateUserPoolDomainRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("Domain", rootObject, domain);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);

            if (rootObject->has("CustomDomainConfig")) {
                customDomainConfig.FromJson(rootObject->getObject("CustomDomainConfig"));
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolDomainRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Domain", domain);
            rootJson.set("UserPoolId", userPoolId);

            rootJson.set("CustomDomainConfig", customDomainConfig.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolDomainRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolDomainRequest &r) {
        os << "CreateUserPoolDomainRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito