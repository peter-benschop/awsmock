//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/dto/module/Module.h>

namespace AwsMock::Dto::Module {

  std::string Module::ToJson(const Database::Entity::Module::Module &module) {
    try {
      Poco::JSON::Object moduleJson;
      moduleJson.set("name", module.name);
      moduleJson.set("executable", module.executable);
      moduleJson.set("port", module.port);
      moduleJson.set("status", Database::Entity::Module::ModuleStatusToString(module.status));
      moduleJson.set("created", Poco::DateTimeFormatter().format(module.created, Poco::DateTimeFormat::HTTP_FORMAT));
      moduleJson.set("modified", Poco::DateTimeFormatter().format(module.modified, Poco::DateTimeFormat::HTTP_FORMAT));

      std::ostringstream os;
      moduleJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string Module::ToJson(const Database::Entity::Module::ModuleList &serviceList) {
    try {
      Poco::JSON::Array moduleJsonArray;
      for (const auto &service : serviceList) {
        Poco::JSON::Object serviceJson;
        serviceJson.set("name", service.name);
        serviceJson.set("executable", service.executable);
        serviceJson.set("port", service.port);
        serviceJson.set("status", Database::Entity::Module::ModuleStatusToString(service.status));
        serviceJson.set("created", Poco::DateTimeFormatter().format(service.created, Poco::DateTimeFormat::HTTP_FORMAT));
        serviceJson.set("modified", Poco::DateTimeFormatter().format(service.modified, Poco::DateTimeFormat::HTTP_FORMAT));
        moduleJsonArray.add(serviceJson);
      }

      std::ostringstream os;
      moduleJsonArray.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Module Module::FromJson(const std::string &payload) {
    if (payload.empty()) {
      return {};
    }
    Module module;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueString("name", rootObject, module.name);
      Core::JsonUtils::GetJsonValueString("executable", rootObject, module.executable);
      Core::JsonUtils::GetJsonValueInt("port", rootObject, module.port);
      if (rootObject->has("status")) {
        module.status = Database::Entity::Module::ModuleStatusFromString(rootObject->get("status").convert<std::string>());
      }

      // Cleanup
      parser.reset();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return module;
  }

  std::vector<Module> Module::FromJsonList(const std::string &payload) {
    if (payload.empty()) {
      return {};
    }
    std::vector<Module> modules;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();

    try {
      for (const auto &jsonModule : *rootArray) {
        Module module;
        Core::JsonUtils::GetJsonValueString("name", jsonModule.extract<Poco::JSON::Object::Ptr>(), module.name);
        Core::JsonUtils::GetJsonValueString("executable", jsonModule.extract<Poco::JSON::Object::Ptr>(), module.executable);
        Core::JsonUtils::GetJsonValueInt("port", jsonModule.extract<Poco::JSON::Object::Ptr>(), module.port);
        if (jsonModule.extract<Poco::JSON::Object::Ptr>()->has("status")) {
          module.status = Database::Entity::Module::ModuleStatusFromString(jsonModule.extract<Poco::JSON::Object::Ptr>()->get("status").convert<std::string>());
        }
        modules.emplace_back(module);
      }

      // Cleanup
      parser.reset();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return modules;
  }

  std::string Module::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Module &m) {
    os << "Module={name='" << m.name << "', executable='" << m.executable << "', port=" << m.port << "'}";
    return os;
  }

} // namespace AwsMock::Dto
