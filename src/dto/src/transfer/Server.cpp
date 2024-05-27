//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/Server.h>

namespace AwsMock::Dto::Transfer {

    Poco::JSON::Object Handler::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Arn", arn);
            rootJson.set("Domain", domain);
            rootJson.set("IdentityProviderType", identityProviderType);
            rootJson.set("EndpointType", endpointType);
            rootJson.set("LoggingRole", loggingRole);
            rootJson.set("ServerId", serverId);
            rootJson.set("State", state);
            rootJson.set("UserCount", userCount);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Handler::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string Handler::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Handler &r) {
        os << "Handler=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
