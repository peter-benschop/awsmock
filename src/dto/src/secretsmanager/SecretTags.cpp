//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/SecretTags.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> SecretTags::ToDocument() const {

        /* Todo:
        try {

            Poco::JSON::Array rootJson;

            for (const auto &t: tags) {
                Poco::JSON::Object tagJsonObject;
                tagJsonObject.set("Key", t.first);
                tagJsonObject.set("Value", t.second);
                rootJson.add(tagJsonObject);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }

    std::string SecretTags::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    void SecretTags::FromDocument(const view_or_value<view, value> &jsonObject) {

        try {

            //Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            //
            //
            // Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SecretTags::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SecretTags &tags) {
        os << "SecretTags=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager