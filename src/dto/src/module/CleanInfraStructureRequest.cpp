//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/module/CleanInfrastructureRequest.h>

namespace AwsMock::Dto::Module {

    void CleanInfrastructureRequest::FromJson(const std::string &payload) {

        using Core::JsonUtils;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            JsonUtils::GetJsonValueBool("onlyObjects", rootObject, onlyObjects);

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

    std::string CleanInfrastructureRequest::ToJson() const {

        using Core::JsonUtils;

        try {

            Poco::JSON::Object rootJson;
            JsonUtils::SetJsonValueBool(rootJson, "onlyObjects", onlyObjects);

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

    std::string CleanInfrastructureRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CleanInfrastructureRequest &r) {
        os << "CleanInfrastructureRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Module