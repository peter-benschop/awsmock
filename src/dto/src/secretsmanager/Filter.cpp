//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Filter.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> Filter::ToDocument() const {

        /* Todo:
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Key", key);

            Poco::JSON::Array valueArray;
            for (const auto &v: values) {
                valueArray.add(v);
            }
            rootJson.set("Values", valueArray);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    void Filter::FromJsonObject(const view_or_value<view, value> &document) {
        /* Todo:
        try {

            Core::JsonUtils::GetJsonValueString("Key", jsonObject, key);
            Poco::JSON::Array::Ptr jsonValueArray = jsonObject->getArray("Values");
            for (std::size_t i = 0; i < jsonValueArray->size(); i++) {
                std::string value = jsonValueArray->getElement<std::string>(i);
                values.emplace_back(value);
            }
        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string Filter::ToJson() const {

        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Filter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Filter &tags) {
        os << "Filter=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager