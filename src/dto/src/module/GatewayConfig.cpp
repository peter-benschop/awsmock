//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/dto/module/GatewayConfig.h>

namespace AwsMock::Dto::Module {

  std::string GatewayConfig::ToJson(const GatewayConfig &gatewayConfig) {
    try {
      Poco::JSON::Object gatewayConfigJson;
      gatewayConfigJson.set("region", gatewayConfig.region);
      gatewayConfigJson.set("protocol", gatewayConfig.protocol);
      gatewayConfigJson.set("endpoint", gatewayConfig.endpoint);
      gatewayConfigJson.set("host", gatewayConfig.host);
      gatewayConfigJson.set("port", gatewayConfig.port);
      gatewayConfigJson.set("accessId", gatewayConfig.accessId);
      gatewayConfigJson.set("clientId", gatewayConfig.clientId);
      gatewayConfigJson.set("user", gatewayConfig.user);
      gatewayConfigJson.set("dataDir", gatewayConfig.dataDir);
      gatewayConfigJson.set("prettyPrint", gatewayConfig.prettyPrint);
      gatewayConfigJson.set("databaseActive", gatewayConfig.databaseActive);

      std::ostringstream os;
      gatewayConfigJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
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
      Core::JsonUtils::GetJsonValueInt("port", rootObject, gatewayConfig.port);
      Core::JsonUtils::GetJsonValueString("accessId", rootObject, gatewayConfig.accessId);
      Core::JsonUtils::GetJsonValueString("clientId", rootObject, gatewayConfig.clientId);
      Core::JsonUtils::GetJsonValueString("user", rootObject, gatewayConfig.user);
      Core::JsonUtils::GetJsonValueString("dataDir", rootObject, gatewayConfig.dataDir);
      Core::JsonUtils::GetJsonValueBool("prettyPrint", rootObject, gatewayConfig.prettyPrint);
      Core::JsonUtils::GetJsonValueBool("databaseActive", rootObject, gatewayConfig.databaseActive);

      // Cleanup
      parser.reset();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return gatewayConfig;
  }

  std::string GatewayConfig::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GatewayConfig &g) {
    os << "GatewayConfig={region='" << g.region << "', protocol='" << g.protocol << "', endpoint=" << g.endpoint << "', host='" << g.host << "', port=" << g.port << ", accessId='" << g.accessId << "', clientId='" << g.clientId << "', user='" << g.user
       << "', dataDir='" << g.dataDir << "', databaseActive=" << (g.databaseActive ? "true" : "false") << "}";
    return os;
  }

} // namespace AwsMock::Dto
