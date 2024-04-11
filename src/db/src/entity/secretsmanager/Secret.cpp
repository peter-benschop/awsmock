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

    view_or_value<view, value> rotationRulesDoc = make_document(
      kvp("automaticallyAfterDays", rotationRules.automaticallyAfterDays),
      kvp("duration", rotationRules.duration),
      kvp("scheduleExpression", rotationRules.scheduleExpression));

    view_or_value<view, value> secretDoc = make_document(
      kvp("region", region),
      kvp("name", name),
      kvp("arn", arn),
      kvp("secretId", secretId),
      kvp("kmsKeyId", kmsKeyId),
      kvp("versionId", versionId),
      kvp("secretString", secretString),
      kvp("secretBinary", secretBinary),
      kvp("description", description),
      kvp("owningService", owningService),
      kvp("primaryRegion", primaryRegion),
      kvp("createdDate", createdDate),
      kvp("deletedDate", deletedDate),
      kvp("lastAccessedDate", lastAccessedDate),
      kvp("lastChangedDate", lastChangedDate),
      kvp("lastRotatedDate", lastRotatedDate),
      kvp("nextRotatedDate", nextRotatedDate),
      kvp("rotationEnabled", rotationEnabled),
      kvp("rotationLambdaARN", rotationLambdaARN),
      kvp("rotationRules", rotationRulesDoc),
      kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
      kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return secretDoc;
  }

  void Secret::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    try {
      oid = mResult.value()["_id"].get_oid().value.to_string();
      region = mResult.value()["region"].get_string().value;
      name = mResult.value()["name"].get_string().value;
      arn = mResult.value()["arn"].get_string().value;
      secretId = mResult.value()["secretId"].get_string().value;
      kmsKeyId = mResult.value()["kmsKeyId"].get_string().value;
      versionId = mResult.value()["versionId"].get_string().value;
      secretString = mResult.value()["secretString"].get_string().value;
      secretBinary = mResult.value()["secretBinary"].get_string().value;
      description = mResult.value()["description"].get_string().value;
      owningService = mResult.value()["owningService"].get_string().value;
      primaryRegion = mResult.value()["primaryRegion"].get_string().value;
      createdDate = mResult.value()["createdDate"].get_int64().value;
      deletedDate = mResult.value()["deletedDate"].get_int64().value;
      lastAccessedDate = mResult.value()["lastAccessedDate"].get_int64().value;
      lastChangedDate = mResult.value()["lastChangedDate"].get_int64().value;
      lastRotatedDate = mResult.value()["lastRotatedDate"].get_int64().value;
      nextRotatedDate = mResult.value()["nextRotatedDate"].get_int64().value;
      rotationEnabled = mResult.value()["rotationEnabled"].get_bool().value;
      rotationLambdaARN = mResult.value()["rotationLambdaARN"].get_string().value;
      created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
      modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

      // Get rotation rules
      if (mResult.value().find("rotationRules") != mResult.value().end()) {
        bsoncxx::document::view rotationView = mResult.value()["rotationRules"].get_document().value;
        rotationRules.automaticallyAfterDays = rotationView["automaticallyAfterDays"].get_int64().value;
        rotationRules.duration = rotationView["duration"].get_string().value;
        rotationRules.scheduleExpression = rotationView["scheduleExpression"].get_string().value;
      }
    } catch (const mongocxx::exception &exc) {
      Poco::Logger::get("Secret").error("Exception: oid: " + oid + " error: " + exc.what());
    }
  }

  Poco::JSON::Object Secret::ToJsonObject() const {

    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("name", name);
    jsonObject.set("arn", arn);
    jsonObject.set("secretId", secretId);
    jsonObject.set("kmsKeyId", kmsKeyId);
    jsonObject.set("versionId", versionId);
    jsonObject.set("secretString", secretString);
    jsonObject.set("secretBinary", secretBinary);
    jsonObject.set("description", description);
    jsonObject.set("owningService", owningService);
    jsonObject.set("primaryRegion", primaryRegion);
    jsonObject.set("createdDate", createdDate);
    jsonObject.set("deletedDate", deletedDate);
    jsonObject.set("lastAccessedDate", lastAccessedDate);
    jsonObject.set("lastChangedDate", lastChangedDate);
    jsonObject.set("lastRotatedDate", lastRotatedDate);
    jsonObject.set("nextRotatedDate", nextRotatedDate);
    jsonObject.set("rotationEnabled", rotationEnabled);
    jsonObject.set("rotationLambdaARN", rotationLambdaARN);
    jsonObject.set("RotationRules", rotationRules.ToJsonObject());
    return jsonObject;

  }

  /**
   * Converts the JSON object to an entity
   *
   * @param jsonObject JSON object.
   */
  void Secret::FromJsonObject(const Poco::JSON::Object::Ptr& jsonObject) {

    Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
    Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
    Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
    Core::JsonUtils::GetJsonValueString("secretId", jsonObject, secretId);
    Core::JsonUtils::GetJsonValueString("kmsKeyId", jsonObject, kmsKeyId);
    Core::JsonUtils::GetJsonValueString("versionId", jsonObject, versionId);
    Core::JsonUtils::GetJsonValueString("secretString", jsonObject, secretString);
    Core::JsonUtils::GetJsonValueString("secretBinary", jsonObject, secretBinary);
    Core::JsonUtils::GetJsonValueString("description", jsonObject, description);
    Core::JsonUtils::GetJsonValueString("owningService", jsonObject, owningService);
    Core::JsonUtils::GetJsonValueString("primaryRegion", jsonObject, primaryRegion);
    Core::JsonUtils::GetJsonValueLong("createdDate", jsonObject, createdDate);
    Core::JsonUtils::GetJsonValueLong("deletedDate", jsonObject, deletedDate);
    Core::JsonUtils::GetJsonValueLong("lastAccessedDate", jsonObject, lastAccessedDate);
    Core::JsonUtils::GetJsonValueLong("lastRotatedDate", jsonObject, lastRotatedDate);
    Core::JsonUtils::GetJsonValueLong("nextRotatedDate", jsonObject, nextRotatedDate);
    Core::JsonUtils::GetJsonValueBool("rotationEnabled", jsonObject, rotationEnabled);
    Core::JsonUtils::GetJsonValueString("rotationLambdaARN", jsonObject, rotationLambdaARN);
  }

  std::string Secret::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Secret &s) {
    os << "Secret=" << bsoncxx::to_json(s.ToDocument());
    return os;
  }

} // namespace AwsMock::Database::Entity::S3
