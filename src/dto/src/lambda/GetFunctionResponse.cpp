//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string GetFunctionResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("Configuration", configuration.ToJsonObject());
            rootJson.set("Code", code.ToJson());
            rootJson.set("Timeout", timeout);

            if (!tags.empty()) {
                Poco::JSON::Object jsonTags;
                for (const auto &tag: tags) {
                    jsonTags.set(tag.first, tag.second);
                }
                rootJson.set("Tags", jsonTags);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetFunctionResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionResponse &r) {
        os << "GetFunctionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
