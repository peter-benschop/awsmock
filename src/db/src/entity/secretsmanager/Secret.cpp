//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/secretsmanager/Secret.h>

namespace AwsMock::Database::Entity::SecretsManager {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  view_or_value<view, value> Secret::ToDocument() const {

    view_or_value<view, value> messageDoc = make_document(
      kvp("region", region),
      kvp("name", name),
      kvp("arn", arn),
      kvp("secretId", secretId),
      kvp("versionId", versionId),
      kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
      kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return messageDoc;
  }

  void Secret::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = mResult.value()["region"].get_string().value;
    name = mResult.value()["name"].get_string().value;
    arn = mResult.value()["arn"].get_string().value;
    secretId = mResult.value()["secretId"].get_string().value;
    versionId = mResult.value()["versionId"].get_string().value;
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
  }

  std::string Secret::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Secret &m) {
    os << "Secret={oid='" << m.oid << "', name='" << m.name << "', arn='" << m.arn << "', secretId='" << m.secretId << "', versionId='" << m.versionId << "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::S3
