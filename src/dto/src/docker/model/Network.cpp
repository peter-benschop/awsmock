//
// Created by JVO on 22.04.2024.
//

#include "awsmock/dto/docker/model/Network.h"

namespace AwsMock::Dto::Docker {

    void Network::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            this->FromJson(result.extract<Poco::JSON::Object::Ptr>());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Network::FromJson(Poco::JSON::Object::Ptr jsonObject) {

        try {
            Core::JsonUtils::GetJsonValueString("Id", jsonObject, id);
            Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
            Core::JsonUtils::GetJsonValueString("Driver", jsonObject, driver);
            Core::JsonUtils::GetJsonValueString("Scope", jsonObject, scope);
            Core::JsonUtils::GetJsonValueBool("EnableIPv6", jsonObject, ipv6Enabled);
            Core::JsonUtils::GetJsonValueDate("Created", jsonObject, created);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Network::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("Name", name);
            rootJson.set("Driver", driver);
            rootJson.set("Scope", scope);
            rootJson.set("EnableIPv6", ipv6Enabled);
            rootJson.set("Created", created);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Network::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string Network::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Network &n) {
        os << "Network=" << n.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
