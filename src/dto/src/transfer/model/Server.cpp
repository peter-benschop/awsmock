//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/model/Server.h>

namespace AwsMock::Dto::Transfer {

    void Server::FromJson(const std::string &body) {

        // Todo:
        /*
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);
            Core::JsonUtils::GetJsonValueString("Arn", rootObject, arn);
            Core::JsonUtils::GetJsonValueString("Domain", rootObject, domain);
            Core::JsonUtils::GetJsonValueString("EndpointType", rootObject, endpointType);
            Core::JsonUtils::GetJsonValueString("State", rootObject, state);
            Core::JsonUtils::GetJsonValueInt("UserCount", rootObject, userCount);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    view_or_value<view, value> Server::ToDocument() const {

        // todo:
        /*
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
        }*/
    }

    std::string Server::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Server::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Server &r) {
        os << "Server=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
