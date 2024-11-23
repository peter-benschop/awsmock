//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Environment.h>

namespace AwsMock::Database::Entity::Lambda {


    void Environment::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            if (jsonObject->has("variables")) {
                Poco::JSON::Object::Ptr variablesJsonObject = jsonObject->getObject("variables");
                for (size_t i = 0; i < variablesJsonObject->getNames().size(); i++) {
                    const std::string key = jsonObject->getNames()[i];
                    const std::string value = jsonObject->get(key);
                    variables[key] = value;
                }
            }

        } catch (Poco::Exception &e) {
            log_error << "JSON Exception" << e.message();
            throw Core::JsonException(e.message());
        }
    }

    Poco::JSON::Object Environment::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        if (!variables.empty()) {
            Poco::JSON::Array jsonArray;
            for (const auto &[fst, snd]: variables) {
                Poco::JSON::Object object;
                object.set("name", fst);
                object.set("value", snd);
                jsonArray.add(object);
            }
            jsonObject.set("variables", jsonArray);
        }
        return jsonObject;
    }

    void Environment::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        if (mResult.value().find("variables") != mResult.value().end()) {
            auto [value] = mResult.value()["variables"].get_array();
            for (auto &v: value) {
                for (auto &it: v.get_document().value) {
                    variables[std::string{it.key()}] = bsoncxx::string::to_string(it.get_string().value);
                }
            }
        }
    }
}// namespace AwsMock::Database::Entity::Lambda