//
// Created by JVO on 22.04.2024.
//

#include <awsmock/dto/docker/model/Network.h>

namespace AwsMock::Dto::Docker {

    void Network::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            FromDocument(document.view());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Network::FromDocument(const view_or_value<view, value> &document) {

        try {
            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            driver = Core::Bson::BsonUtils::GetStringValue(document, "Driver");
            scope = Core::Bson::BsonUtils::GetStringValue(document, "Scope");
            ipv6Enabled = Core::Bson::BsonUtils::GetBoolValue(document, "EnableIPv6");
            created = Core::Bson::BsonUtils::GetDateValue(document, "Created");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Network::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Driver", driver);
            Core::Bson::BsonUtils::SetStringValue(document, "Scope", scope);
            Core::Bson::BsonUtils::SetBoolValue(document, "EnableIPv6", ipv6Enabled);
            Core::Bson::BsonUtils::SetDateValue(document, "Created", created);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Network::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Network::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Network &n) {
        os << "Network=" << n.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
