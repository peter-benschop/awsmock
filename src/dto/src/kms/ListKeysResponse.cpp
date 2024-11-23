//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ListKeysResponse.h>

namespace AwsMock::Dto::KMS {

    void ListKeysResponse::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("NextMarker", rootObject, nextMarker);
            Core::JsonUtils::GetJsonValueBool("Truncated", rootObject, truncated);

            Poco::JSON::Array::Ptr jsonKeyArray = rootObject->getArray("Keys");
            for (int i = 0; i < jsonKeyArray->size(); i++) {
                ListKey key;
                Poco::JSON::Object::Ptr jsonKeyObject = jsonKeyArray->getObject(i);
                Core::JsonUtils::GetJsonValueString("KeyId", jsonKeyObject, key.keyId);
                Core::JsonUtils::GetJsonValueString("KeyArn", jsonKeyObject, key.keyArn);
                keys.emplace_back(key);
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListKeysResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("NextMarker", nextMarker);
            rootJson.set("Truncated", truncated);

            Poco::JSON::Array keyArray;
            for (const auto &key: keys) {
                keyArray.add(key.ToJsonObject());
            }
            rootJson.set("Keys", keyArray);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListKeysResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListKeysResponse &r) {
        os << "ListKeysRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
