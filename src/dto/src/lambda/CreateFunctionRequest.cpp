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

            // Tags
            Poco::JSON::Array tagsArray;
            for (const auto &[fst, snd]: tags) {
                Poco::JSON::Object tagObject;
                tagObject.set(fst, snd);
                tagsArray.add(tagObject);
            }
            rootJson.set("Tags", tagsArray);

            // Ephemeral storage
            //rootJson.set("EphemeralStorage", ephemeralStorage.ToJsonObject());

            // Code
            rootJson.set("Code", code.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateFunctionRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        const Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
            Core::JsonUtils::GetJsonValueString("Runtime", rootObject, runtime);
            Core::JsonUtils::GetJsonValueString("Role", rootObject, role);
            Core::JsonUtils::GetJsonValueString("Handler", rootObject, handler);
            Core::JsonUtils::GetJsonValueInt("Timeout", rootObject, timeout);
            Core::JsonUtils::GetJsonValueLong("MemorySize", rootObject, memorySize);

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
                environment.FromJson(rootObject->getObject("Environment"));
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
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateFunctionRequest &r) {
        os << "CreateFunctionRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
