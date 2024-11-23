//
// Created by vogje01 on 13/09/2023.
//

#include "awsmock/core/JsonUtils.h"
#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database::Entity::Transfer {

    view_or_value<view, value> User::ToDocument() const {

        view_or_value<view, value> userDoc = make_document(
                kvp("arn", arn),
                kvp("role", role),
                kvp("userName", userName),
                kvp("password", password),
                kvp("homeDirectory", homeDirectory));

        return userDoc;
    }

    void User::FromDocument(bsoncxx::document::view mResult) {

        for (auto &v: mResult) {
            arn = bsoncxx::string::to_string(v["arn"].get_string().value);
            role = bsoncxx::string::to_string(v["role"].get_string().value);
            userName = bsoncxx::string::to_string(v["userName"].get_string().value);
            password = bsoncxx::string::to_string(v["password"].get_string().value);
            homeDirectory = bsoncxx::string::to_string(v["homeDirectory"].get_string().value);
        }
    }

    void User::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
        Core::JsonUtils::GetJsonValueString("role", jsonObject, role);
        Core::JsonUtils::GetJsonValueString("userName", jsonObject, userName);
        Core::JsonUtils::GetJsonValueString("password", jsonObject, password);
        Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
        Core::JsonUtils::GetJsonValueString("homeDirectory", jsonObject, homeDirectory);
    }

    Poco::JSON::Object User::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("arn", arn);
        jsonObject.set("role", role);
        jsonObject.set("userName", userName);
        jsonObject.set("password", password);
        jsonObject.set("homeDirectory", homeDirectory);

        return jsonObject;
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &u) {
        os << "User=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::Transfer