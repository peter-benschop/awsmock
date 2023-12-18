//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/DynamoDb.h>

namespace AwsMock::Database::Entity::DynamoDb {

  view_or_value<view, value> DynamoDb::ToDocument() const {

    view_or_value<view, value> lambdaDoc = make_document(
      kvp("region", region),
      kvp("name", name),
      kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
      kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));
    return lambdaDoc;
  }

  void DynamoDb::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
  }

  Poco::JSON::Object DynamoDb::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("name", name);
    jsonObject.set("created", Poco::DateTimeFormatter::format(created, Poco::DateTimeFormat::ISO8601_FORMAT));
    jsonObject.set("modified", Poco::DateTimeFormatter::format(modified, Poco::DateTimeFormat::ISO8601_FORMAT));

    return jsonObject;
  }

  std::string DynamoDb::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DynamoDb &d) {
    os << "DynamoDb={oid='" << d.oid << "', region='" << d.region << "', name='" << d.name
       << "', created='" << Poco::DateTimeFormatter::format(d.created, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', modified='" << Poco::DateTimeFormatter::format(d.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
    return os;
  }
}