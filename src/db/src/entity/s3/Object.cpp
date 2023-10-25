//
// Created by vogje01 on 03/09/2023.
//

#include "awsmock/entity/s3/Object.h"

namespace AwsMock::Database::Entity::S3 {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  view_or_value<view, value> Object::ToDocument() const {

      auto metadataDoc = bsoncxx::builder::basic::document{};
      for (const auto &m : metadata) {
          metadataDoc.append(kvp(m.first, m.second));
      }

      view_or_value<view, value> objectDoc = make_document(
          kvp("region", region),
          kvp("bucket", bucket),
          kvp("key", key),
          kvp("owner", owner),
          kvp("size", size),
          kvp("md5sum", md5sum),
          kvp("sha1sum", sha1sum),
          kvp("sha256sum", sha256sum),
          kvp("contentType", contentType),
          kvp("metadata", metadataDoc),
          kvp("internalName", internalName),
          kvp("versionId", versionId),
          kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
          kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

      return objectDoc;
  }

  void Object::FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

      oid = mResult.value()["_id"].get_oid().value.to_string();
      region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
      bucket = bsoncxx::string::to_string(mResult.value()["bucket"].get_string().value);
      key = bsoncxx::string::to_string(mResult.value()["key"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      size = mResult.value()["size"].get_int64().value;
      md5sum = bsoncxx::string::to_string(mResult.value()["md5sum"].get_string().value);
      sha1sum = bsoncxx::string::to_string(mResult.value()["sha1sum"].get_string().value);
      sha256sum = bsoncxx::string::to_string(mResult.value()["sha256sum"].get_string().value);
      contentType = bsoncxx::string::to_string(mResult.value()["contentType"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      internalName = bsoncxx::string::to_string(mResult.value()["internalName"].get_string().value);
      versionId = bsoncxx::string::to_string(mResult.value()["versionId"].get_string().value);
      created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
      modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

      // Get metadata
      bsoncxx::document::view metadataView = mResult.value()["metadata"].get_document().value;
      for (bsoncxx::document::element metadataElement : metadataView) {
          std::string metadataKey = bsoncxx::string::to_string(metadataElement.key());
          std::string metadataValue = bsoncxx::string::to_string(metadataView[metadataKey].get_string().value);
          metadata.emplace(metadataKey, metadataValue);
      }
  }

  void Object::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {
      oid = mResult.value()["_id"].get_oid().value.to_string();
      region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
      bucket = bsoncxx::string::to_string(mResult.value()["bucket"].get_string().value);
      key = bsoncxx::string::to_string(mResult.value()["key"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      size = mResult.value()["size"].get_int64().value;
      md5sum = bsoncxx::string::to_string(mResult.value()["md5sum"].get_string().value);
      sha1sum = bsoncxx::string::to_string(mResult.value()["sha1sum"].get_string().value);
      sha256sum = bsoncxx::string::to_string(mResult.value()["sha256sum"].get_string().value);
      contentType = bsoncxx::string::to_string(mResult.value()["contentType"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      internalName = bsoncxx::string::to_string(mResult.value()["internalName"].get_string().value);
      versionId = bsoncxx::string::to_string(mResult.value()["versionId"].get_string().value);
      created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
      modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

      // Get metadata
      bsoncxx::document::view metadataView = mResult.value()["metadata"].get_document().value;
      for (bsoncxx::document::element metadataElement : metadataView) {
          std::string metadataKey = bsoncxx::string::to_string(metadataElement.key());
          std::string metadataValue = bsoncxx::string::to_string(metadataView[metadataKey].get_string().value);
          metadata.emplace(metadataKey, metadataValue);
      }
  }

  std::string Object::ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Object &o) {
      os << "Object={id='" << o.oid << "', bucket='" << o.bucket << "', key='" << o.key << "', owner='" << o.owner << "', size='" << o.size << "', md5sum='"
         << o.md5sum << "', contentType='" << o.contentType << ", internalName='" << o.internalName << "', versionId='" << o.versionId << "', metadata=[";
      for (const auto &t : o.metadata) {
          os << t.first << "=" << t.second << ", ";
      }
      os << "\b\b" << "]}";
      return os;
  }

}