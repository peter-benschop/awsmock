//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/IdentityProviderDetails.h>

namespace AwsMock::Dto::Transfer {

    std::string IdentityProviderDetails::ToJson() const {

        // Todo:
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("directoryId", directoryId);
            rootJson.set("function", function);
            rootJson.set("url", url);
            rootJson.set("invocationRole", invocationRole);
            rootJson.set("sftpAuthenticationMethods", sftpAuthenticationMethods);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
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
