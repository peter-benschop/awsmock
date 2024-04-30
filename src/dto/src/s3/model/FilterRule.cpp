//
// Created by vogje01 on 4/28/24.
//

#include <awsmock/dto/s3/model/FilterRule.h>

namespace AwsMock::Dto::S3 {

    void FilterRule::FromXmlNode(Poco::XML::Node *rootNode) {

        name = NameTypeFromString(rootNode->firstChild()->innerText());
        value = rootNode->lastChild()->innerText();
    }

    Poco::JSON::Object FilterRule::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("name", NameTypeToString(name));
            rootJson.set("value", value);
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string FilterRule::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    void FilterRule::FromJson(Poco::JSON::Object::Ptr jsonObject) {

        try {

            if (jsonObject->has("S3Key")) {
            }
            Core::JsonUtils::GetJsonValueString("value", jsonObject, value);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string FilterRule::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const FilterRule &s) {
        os << "FilterRule=" << s.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
