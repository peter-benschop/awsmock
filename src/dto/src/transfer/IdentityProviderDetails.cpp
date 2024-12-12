//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/IdentityProviderDetails.h>

namespace AwsMock::Dto::Transfer {

    std::string IdentityProviderDetails::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "directoryId", directoryId);
            Core::Bson::BsonUtils::SetStringValue(document, "function", function);
            Core::Bson::BsonUtils::SetStringValue(document, "url", url);
            Core::Bson::BsonUtils::SetStringValue(document, "invocationRole", invocationRole);
            Core::Bson::BsonUtils::SetStringValue(document, "sftpAuthenticationMethods", sftpAuthenticationMethods);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string IdentityProviderDetails::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const IdentityProviderDetails &r) {
        os << "IdentityProviderDetails=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
