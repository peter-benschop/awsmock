//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/model/Server.h>

namespace AwsMock::Dto::Transfer {

    void Server::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            serverId = Core::Bson::BsonUtils::GetStringValue(document, "ServerId");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "Arn");
            domain = Core::Bson::BsonUtils::GetStringValue(document, "Domain");
            endpointType = Core::Bson::BsonUtils::GetStringValue(document, "EndpointType");
            state = Core::Bson::BsonUtils::GetStringValue(document, "State");
            userCount = Core::Bson::BsonUtils::GetIntValue(document, "UserCount");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Server::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "ServerId", serverId);
            Core::Bson::BsonUtils::SetStringValue(document, "Arn", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "Domain", domain);
            Core::Bson::BsonUtils::SetStringValue(document, "IdentityProviderType", identityProviderType);
            Core::Bson::BsonUtils::SetStringValue(document, "EndpointType", endpointType);
            Core::Bson::BsonUtils::SetStringValue(document, "LoggingRole", loggingRole);
            Core::Bson::BsonUtils::SetStringValue(document, "State", state);
            Core::Bson::BsonUtils::SetIntValue(document, "UserCount", userCount);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
