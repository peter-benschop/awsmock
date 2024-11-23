//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/SecretTags.h>

namespace AwsMock::Dto::SecretsManager {

    Poco::JSON::Array SecretTags::ToJsonArray() const {

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
        }
    }

    std::string SecretTags::ToJson() const {

        std::ostringstream os;
        ToJsonArray().stringify(os);
        return os.str();
    }

    void SecretTags::FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            //Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            //
            //
            // Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
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