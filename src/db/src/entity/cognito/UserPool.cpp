//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Database::Entity::Cognito {

  view_or_value<view, value> UserPool::ToDocument() const {

    view_or_value<view, value> userPoolDocument = make_document(
        kvp("region", region),
        kvp("userPoolId", userPoolId),
        kvp("name", name),
        kvp("clientId", clientId),
        kvp("created",
            bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified",
            bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));
    return userPoolDocument;

  }

  void UserPool::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    userPoolId = bsoncxx::string::to_string(mResult.value()["userPoolId"].get_string().value);
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    clientId = bsoncxx::string::to_string(mResult.value()["clientId"].get_string().value);
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

  }

  Poco::JSON::Object UserPool::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("userPoolId", userPoolId);
    jsonObject.set("name", name);
    jsonObject.set("clientId", clientId);
    return jsonObject;
  }

  void UserPool::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

    Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
    Core::JsonUtils::GetJsonValueString("userPoolId", jsonObject, userPoolId);
    Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
    Core::JsonUtils::GetJsonValueString("clientId", jsonObject, clientId);
  }

  std::string UserPool::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UserPool &u) {
    os << "UserPool=" << bsoncxx::to_json(u.ToDocument());
    return os;
  }
}