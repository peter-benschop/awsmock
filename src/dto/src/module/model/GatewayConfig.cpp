//
// Created by vogje01 on 10/23/23.
//

#include "awsmock/dto/module/model/GatewayConfig.h"

namespace AwsMock::Dto::Module {

    std::string GatewayConfig::ToJson() const {
        try {
            Poco::JSON::Object gatewayConfigJson;
            gatewayConfigJson.set("region", region);
            gatewayConfigJson.set("protocol", protocol);
            gatewayConfigJson.set("endpoint", endpoint);
            gatewayConfigJson.set("host", host);
            gatewayConfigJson.set("address", address);
            gatewayConfigJson.set("port", port);
            gatewayConfigJson.set("pid", pid);
            gatewayConfigJson.set("pretty", prettyPrint);
            gatewayConfigJson.set("accessId", accessId);
            gatewayConfigJson.set("clientId", clientId);
            gatewayConfigJson.set("user", user);
            gatewayConfigJson.set("dataDir", dataDir);
            gatewayConfigJson.set("prettyPrint", prettyPrint);
            gatewayConfigJson.set("databaseActive", databaseActive);
            gatewayConfigJson.set("version", version);

            return Core::JsonUtils::ToJsonString(gatewayConfigJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    GatewayConfig GatewayConfig::FromJson(const std::string &payload) {
        if (payload.empty()) {
            return {};
        }
        GatewayConfig gatewayConfig;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("region", rootObject, gatewayConfig.region);
            Core::JsonUtils::GetJsonValueString("protocol", rootObject, gatewayConfig.protocol);
            Core::JsonUtils::GetJsonValueString("endpoint", rootObject, gatewayConfig.endpoint);
            Core::JsonUtils::GetJsonValueString("host", rootObject, gatewayConfig.host);
            Core::JsonUtils::GetJsonValueString("address", rootObject, gatewayConfig.address);
            Core::JsonUtils::GetJsonValueInt("port", rootObject, gatewayConfig.port);
            Core::JsonUtils::GetJsonValueInt("pid", rootObject, gatewayConfig.pid);
            Core::JsonUtils::GetJsonValueBool("prettyPrint", rootObject, gatewayConfig.prettyPrint);
            Core::JsonUtils::GetJsonValueString("accessId", rootObject, gatewayConfig.accessId);
            Core::JsonUtils::GetJsonValueString("clientId", rootObject, gatewayConfig.clientId);
            Core::JsonUtils::GetJsonValueString("user", rootObject, gatewayConfig.user);
            Core::JsonUtils::GetJsonValueString("dataDir", rootObject, gatewayConfig.dataDir);
            Core::JsonUtils::GetJsonValueBool("prettyPrint", rootObject, gatewayConfig.prettyPrint);
            Core::JsonUtils::GetJsonValueBool("databaseActive", rootObject, gatewayConfig.databaseActive);
            Core::JsonUtils::GetJsonValueString("version", rootObject, gatewayConfig.version);

            // Cleanup
            parser.reset();

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
        return gatewayConfig;
    }

    std::string GatewayConfig::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GatewayConfig &g) {
        os << "GatewayConfig=" << g.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Module
