//
// Created by vogje01 on 10/23/23.
//

#include "awsmock/dto/module/model/Module.h"

namespace AwsMock::Dto::Module {

    std::string Module::ToJson() const {

        using Core::JsonUtils;

        try {
            Poco::JSON::Object moduleJson;
            JsonUtils::SetJsonValueString(moduleJson, "name", name);
            JsonUtils::SetJsonValueString(moduleJson, "executable", executable);
            JsonUtils::SetJsonValueInt(moduleJson, "port", port);
            JsonUtils::SetJsonValueString(moduleJson, "state", Database::Entity::Module::ModuleStateToString(status));
            JsonUtils::SetJsonValueDate(moduleJson, "created", created);
            JsonUtils::SetJsonValueDate(moduleJson, "modified", modified);

            return Core::JsonUtils::ToJsonString(moduleJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Module::ToJson(const Database::Entity::Module::ModuleList &serviceList) {

        using Core::JsonUtils;

        try {

            Poco::JSON::Array moduleJsonArray;
            for (const auto &service: serviceList) {
                Poco::JSON::Object serviceJson;
                JsonUtils::SetJsonValueString(serviceJson, "name", service.name);
                JsonUtils::SetJsonValueInt(serviceJson, "port", service.port);
                JsonUtils::SetJsonValueString(serviceJson, "state", Database::Entity::Module::ModuleStateToString(service.state));
                JsonUtils::SetJsonValueDate(serviceJson, "created", service.created);
                JsonUtils::SetJsonValueDate(serviceJson, "modified", service.modified);
                moduleJsonArray.add(serviceJson);
            }

            return Core::JsonUtils::ToJsonString(moduleJsonArray);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Module::ToJson(const ModuleList &moduleList) {

        using Core::JsonUtils;

        try {

            Poco::JSON::Array moduleJsonArray;
            for (const auto &module: moduleList) {
                Poco::JSON::Object moduleJson;
                JsonUtils::SetJsonValueString(moduleJson, "name", module.name);
                JsonUtils::SetJsonValueInt(moduleJson, "port", module.port);
                JsonUtils::SetJsonValueString(moduleJson, "status", Database::Entity::Module::ModuleStateToString(module.status));
                JsonUtils::SetJsonValueDate(moduleJson, "created", module.created);
                JsonUtils::SetJsonValueDate(moduleJson, "modified", module.modified);
                moduleJsonArray.add(moduleJson);
            }

            return Core::JsonUtils::ToJsonString(moduleJsonArray);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Module Module::FromJson(const std::string &payload) {

        if (payload.empty()) {
            return {};
        }

        Module module;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("name", rootObject, module.name);
            Core::JsonUtils::GetJsonValueInt("port", rootObject, module.port);
            if (rootObject->has("state")) {
                module.status = Database::Entity::Module::ModuleStateFromString(rootObject->get("state").convert<std::string>());
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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
            for (const auto &jsonModule: *rootArray) {
                Module module;
                Core::JsonUtils::GetJsonValueString("name", jsonModule.extract<Poco::JSON::Object::Ptr>(), module.name);
                Core::JsonUtils::GetJsonValueInt("port", jsonModule.extract<Poco::JSON::Object::Ptr>(), module.port);
                if (jsonModule.extract<Poco::JSON::Object::Ptr>()->has("state")) {
                    module.status = Database::Entity::Module::ModuleStateFromString(jsonModule.extract<Poco::JSON::Object::Ptr>()->get("state").convert<std::string>());
                }
                modules.emplace_back(module);
            }

            // Cleanup
            parser.reset();

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
        return modules;
    }

    std::string Module::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Module &m) {
        os << "Module=" << m.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Module
