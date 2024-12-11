//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/UpdateUserPoolDomainResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string UpdateUserPoolDomainResponse::ToJson() const {
        // TODO:: fix me
        /*try {

            Poco::JSON::Object rootObject;
            rootObject.set("CloudFrontDomain", cloudFrontDomain);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string UpdateUserPoolDomainResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateUserPoolDomainResponse &r) {
        os << "UpdateUserPoolDomainResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito