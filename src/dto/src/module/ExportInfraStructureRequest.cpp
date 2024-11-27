//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/module/ExportInfrastructureRequest.h>

namespace AwsMock::Dto::Module {

    void ExportInfrastructureRequest::FromJson(const std::string &payload) {

        using Core::JsonUtils;

        Poco::JSON::Parser parser;
        const Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            JsonUtils::GetJsonValueBool("includeObjects", rootObject, includeObjects);
            JsonUtils::GetJsonValueBool("prettyPrint", rootObject, prettyPrint);

            if (rootObject->has("modules")) {
                Poco::JSON::Array::Ptr jsonArray = rootObject->getArray("modules");
                for (auto &it: *jsonArray) {
                    modules.emplace_back(it);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ExportInfrastructureRequest::ToJson() const {

        using Core::JsonUtils;

        try {

            Poco::JSON::Object rootJson;
            JsonUtils::SetJsonValueBool(rootJson, "includeObjects", includeObjects);
            JsonUtils::SetJsonValueBool(rootJson, "prettyPrint", prettyPrint);

            if (!modules.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &it: modules) {
                    jsonArray.add(it);
                }
                rootJson.set("modules", jsonArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ExportInfrastructureRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ExportInfrastructureRequest &r) {
        os << "ExportInfrastructureRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Module