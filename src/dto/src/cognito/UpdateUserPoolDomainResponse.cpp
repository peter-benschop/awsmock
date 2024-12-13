//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/UpdateUserPoolDomainResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string UpdateUserPoolDomainResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "CloudFrontDomain", cloudFrontDomain);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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