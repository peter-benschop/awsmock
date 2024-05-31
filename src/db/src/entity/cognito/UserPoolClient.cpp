//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/UserPoolClient.h>

namespace AwsMock::Database::Entity::Cognito {

    view_or_value<view, value> UserPoolClient::ToDocument() const {

        view_or_value<view, value> userPoolDocument = make_document(
                kvp("userPoolId", userPoolId),
                kvp("clientId", clientId),
                kvp("clientName", clientName),
                kvp("clientSecret", clientSecret),
                kvp("generateSecret", generateSecret),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));
        return userPoolDocument;
    }

    void UserPoolClient::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {

            userPoolId = bsoncxx::string::to_string(mResult.value()["userPoolId"].get_string().value);
            clientId = bsoncxx::string::to_string(mResult.value()["clientId"].get_string().value);
            clientName = bsoncxx::string::to_string(mResult.value()["clientName"].get_string().value);
            clientSecret = bsoncxx::string::to_string(mResult.value()["clientSecret"].get_string().value);
            generateSecret = mResult.value()["generateSecret"].get_bool().value;
            created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
            modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Poco::JSON::Object UserPoolClient::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("userPoolId", userPoolId);
        jsonObject.set("clientId", clientId);
        jsonObject.set("clientName", clientName);
        jsonObject.set("clientSecret", clientSecret);
        jsonObject.set("generateSecret", generateSecret);
        jsonObject.set("created", created);
        jsonObject.set("modified", modified);

        return jsonObject;
    }

    void UserPoolClient::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("userPoolId", jsonObject, userPoolId);
        Core::JsonUtils::GetJsonValueString("clientId", jsonObject, clientId);
        Core::JsonUtils::GetJsonValueString("clientName", jsonObject, clientName);
        Core::JsonUtils::GetJsonValueString("clientSecret", jsonObject, clientSecret);
        Core::JsonUtils::GetJsonValueBool("generateSecret", jsonObject, generateSecret);
        Core::JsonUtils::GetJsonValueDate("created", jsonObject, created);
        Core::JsonUtils::GetJsonValueDate("modified", jsonObject, modified);
    }

    std::string UserPoolClient::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserPoolClient &u) {
        os << "UserPoolClient=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::Cognito