//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/Item.h>

namespace AwsMock::Database::Entity::DynamoDb {

  view_or_value<view, value> Item::ToDocument() const {

    view_or_value<view, value> lambdaDoc = make_document(
      kvp("region", region),
      kvp("name", name),
      kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
      kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return lambdaDoc;
  }

  void Item::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
  }

  Poco::JSON::Object Item::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("name", name);

    return jsonObject;
  }

  std::string Item::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Item &i) {
    os << "Item={oid='" << i.oid << "', region='" << i.region << "', name='" << i.name << "'}";
    return os;
  }
}