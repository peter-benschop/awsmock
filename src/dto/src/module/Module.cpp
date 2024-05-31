//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/dto/module/Module.h>

namespace AwsMock::Dto::Module {

    std::string Module::ToJson() const {
        try {
            Poco::JSON::Object moduleJson;
            moduleJson.set("name", name);
            moduleJson.set("executable", executable);
            moduleJson.set("port", port);
            moduleJson.set("state", Database::Entity::Module::ModuleStateToString(status));
            moduleJson.set("created", Core::DateTimeUtils::ISO8601(created));
            moduleJson.set("modified", Core::DateTimeUtils::ISO8601(modified));

            return Core::JsonUtils::ToJsonString(moduleJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Module::ToJson(const Database::Entity::Module::ModuleList &serviceList) {
        try {
            Poco::JSON::Array moduleJsonArray;
            for (const auto &service: serviceList) {
                Poco::JSON::Object serviceJson;
                serviceJson.set("name", service.name);
                serviceJson.set("port", service.port);
                serviceJson.set("state", Database::Entity::Module::ModuleStateToString(service.state));
                serviceJson.set("created", Core::DateTimeUtils::ISO8601(service.created));
                serviceJson.set("modified", Core::DateTimeUtils::ISO8601(service.modified));
                moduleJsonArray.add(serviceJson);
            }

            return Core::JsonUtils::ToJsonString(moduleJsonArray);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Module::ToJson(const ModuleList &moduleList) {
        try {
            Poco::JSON::Array moduleJsonArray;
            for (const auto &module: moduleList) {
                Poco::JSON::Object moduleJson;
                moduleJson.set("name", module.name);
                moduleJson.set("port", module.port);
                moduleJson.set("status", Database::Entity::Module::ModuleStateToString(module.status));
                moduleJson.set("created", Core::DateTimeUtils::ISO8601(module.created));
                moduleJson.set("modified", Core::DateTimeUtils::ISO8601(module.modified));
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
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

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
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Module &m) {
        os << "Module=" << m.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Module
