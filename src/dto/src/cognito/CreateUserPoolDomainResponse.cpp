//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolDomainResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateUserPoolDomainResponse::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "CloudFrontDomain", cloudFrontDomain);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateUserPoolDomainResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolDomainResponse &r) {
        os << "CreateUserPoolDomainResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito