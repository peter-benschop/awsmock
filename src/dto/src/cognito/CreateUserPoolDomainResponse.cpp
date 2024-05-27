//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolDomainResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateUserPoolDomainResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            rootObject.set("Region", region);
            rootObject.set("CloudFrontDomain", cloudFrontDomain);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolDomainResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolDomainResponse &r) {
        os << "CreateUserPoolDomainResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito