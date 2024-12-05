//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/model/Key.h>
#include <bsoncxx/builder/basic/document.hpp>

namespace AwsMock::Dto::DynamoDb {

    Poco::JSON::Object Key::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;

            for (const auto &[fst, snd]: keys) {
                rootJson.set(fst, snd.ToJsonObject());
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Key::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            for (size_t i = 0; i < jsonObject->getNames().size(); i++) {
                std::string name = jsonObject->getNames()[i];
                Poco::JSON::Object::Ptr keyObject = jsonObject->getObject(name);
                AttributeValue attributeValue;
                attributeValue.FromJsonObject(keyObject);
                keys[name] = attributeValue;
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Key::FromDocument(const bsoncxx::document::view &document) {

        try {
            for (bsoncxx::document::element ele: document) {

                std::string name(ele.key());
                AttributeValue attributeValue;
                attributeValue.FromDocument(ele.get_document());
                keys[name] = attributeValue;
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Key::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string Key::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Key &r) {
        os << "Key=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
