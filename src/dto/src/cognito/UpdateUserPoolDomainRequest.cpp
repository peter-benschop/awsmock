//
// Created by vogje01 on 11/25/23.
//

#include "awsmock/dto/cognito/UpdateUserPoolDomainRequest.h"

namespace AwsMock::Dto::Cognito {

    void UpdateUserPoolDomainRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueString("Domain", rootObject, domain);

            if (rootObject->has("CustomDomainConfig")) {
                customDomainConfig.FromJsonObject(rootObject->getObject("CustomDomainConfig"));
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateUserPoolDomainRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("Domain", domain);
            rootJson.set("CustomDomainConfig", customDomainConfig.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateUserPoolDomainRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateUserPoolDomainRequest &r) {
        os << "UpdateUserPoolDomainRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito