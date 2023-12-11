//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Database::Entity::SQS {

  view_or_value<view, value> Queue::ToDocument() const {

    auto tagsDoc = bsoncxx::builder::basic::document{};
    if (!tags.empty()) {
      for (const auto &t : tags) {
        tagsDoc.append(kvp(t.first, t.second));
      }
    }

    view_or_value<view, value> queueDoc = make_document(
      kvp("region", region),
      kvp("name", name),
      kvp("owner", owner),
      kvp("queueUrl", queueUrl),
      kvp("queueArn", queueArn),
      kvp("attributes", attributes.ToDocument()),
      kvp("tags", tagsDoc),
      kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
      kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return queueDoc;
  }

  void Queue::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
    queueUrl = bsoncxx::string::to_string(mResult.value()["queueUrl"].get_string().value);
    queueArn = bsoncxx::string::to_string(mResult.value()["queueArn"].get_string().value);
    attributes.FromDocument(mResult.value()["attributes"].get_document().value);
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    // Get tags
    if (mResult.value().find("tags") != mResult.value().end()) {
      bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
      for (bsoncxx::document::element tagElement : tagsView) {
        std::string key = bsoncxx::string::to_string(tagElement.key());
        std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
        tags.emplace(key, value);
      }
    }
  }

  Poco::JSON::Object Queue::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("name", name);
    jsonObject.set("owner", owner);
    jsonObject.set("queueUrl", queueUrl);
    jsonObject.set("queueArn", queueArn);
    jsonObject.set("attributes", attributes.ToJsonObject());
    return jsonObject;
  }

  void Queue::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

    Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
    Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
    Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
    Core::JsonUtils::GetJsonValueString("queueUrl", jsonObject, queueUrl);
    Core::JsonUtils::GetJsonValueString("queueArn", jsonObject, queueArn);
    Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
    attributes.FromJsonObject(jsonObject->getObject("attributes"));
  }

  std::string Queue::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Queue &q) {
    os << "Queue={id='" << q.oid << "' region='" << q.region << "' name='" << q.name << "' owner='" << q.owner << "' queueUrl='" << q.queueUrl <<
       "' queueArn='" << q.queueArn << "' created='" << Poco::DateTimeFormatter::format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
       "' modified='" << Poco::DateTimeFormatter::format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::SQS
