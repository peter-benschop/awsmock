//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateNetworkResponse.h>

namespace AwsMock::Dto::Docker {

    void CreateNetworkResponse::FromJson(const std::string &jsonString) {

        if (jsonString.empty()) {
            return;
        }

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Id", rootObject, id);
            Core::JsonUtils::GetJsonValueString("Warning", rootObject, warning);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateNetworkResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("Warning", warning);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateNetworkResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateNetworkResponse &r) {
        os << "CreateNetworkResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
