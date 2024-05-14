//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/CreateFunctionRequest.h>

namespace AwsMock::Dto::Lambda {

    std::string CreateFunctionRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("FunctionName", functionName);
            rootJson.set("Runtime", runtime);
            rootJson.set("Role", role);
            rootJson.set("Handler", handler);
            rootJson.set("MemorySize", memorySize);
            rootJson.set("Code", code.ToJsonObject());
            rootJson.set("Timeout", timeout);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateFunctionRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
            Core::JsonUtils::GetJsonValueString("Runtime", rootObject, runtime);
            Core::JsonUtils::GetJsonValueString("Role", rootObject, role);
            Core::JsonUtils::GetJsonValueString("Handler", rootObject, handler);
            Core::JsonUtils::GetJsonValueInt("Timeout", rootObject, timeout);

            // Tags
            if (rootObject->has("Tags")) {
                Poco::JSON::Object::Ptr tagsObject = rootObject->getObject("Tags");
                for (const auto &tag: tagsObject->getNames()) {
                    std::string value;
                    Core::JsonUtils::GetJsonValueString(tag, tagsObject, value);
                    tags[tag] = value;
                }
            }

            // EphemeralStorage
            if (rootObject->has("EphemeralStorage")) {
                ephemeralStorage.FromJson(rootObject->getObject("EphemeralStorage"));
            }

            // Environment
            if (rootObject->has("Environment")) {
                environmentVariables.FromJson(rootObject->getObject("Environment"));
            }

            // Code
            if (rootObject->has("Code")) {
                code.FromJson(rootObject->getObject("Code"));
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateFunctionRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateFunctionRequest &r) {
        os << "CreateFunctionRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
