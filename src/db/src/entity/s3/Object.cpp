//
// Created by vogje01 on 03/09/2023.
//

#include "awsmock/entity/s3/Object.h"

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    view_or_value <view, value> Object::ToDocument() const {

        auto metadataDoc = bsoncxx::builder::basic::document{};
        for (const auto &m: metadata) {
            metadataDoc.append(kvp(m.first, m.second));
        }

        view_or_value <view, value> objectDoc = make_document(
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

    void Object::FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult) {
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
        internalName = bsoncxx::string::to_string(mResult.value()["internalName"].get_string().value);
        versionId = bsoncxx::string::to_string(mResult.value()["versionId"].get_string().value);
        created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
        modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

        // Get metadata
        bsoncxx::document::view metadataView = mResult.value()["metadata"].get_document().value;
        for (bsoncxx::document::element metadataElement: metadataView) {
            std::string metadataKey = bsoncxx::string::to_string(metadataElement.key());
            std::string metadataValue = bsoncxx::string::to_string(metadataView[metadataKey].get_string().value);
            metadata.emplace(metadataKey, metadataValue);
        }
    }

    Poco::JSON::Object Object::ToJsonObject() const {
        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("bucket", bucket);
        jsonObject.set("key", key);
        jsonObject.set("owner", owner);
        jsonObject.set("size", size);
        jsonObject.set("md5sum", md5sum);
        jsonObject.set("sha1sum", sha1sum);
        jsonObject.set("sha256sum", sha256sum);
        jsonObject.set("contentType", contentType);
        jsonObject.set("internalName", internalName);
        jsonObject.set("versionId", versionId);

        Poco::JSON::Array jsonMetadataArray;
        for (const auto &meta: metadata) {
            Poco::JSON::Object jsonMetadata;
            jsonMetadata.set("name", meta.first);
            jsonMetadata.set("value", meta.second);
            jsonMetadataArray.add(jsonMetadata);
        }
        jsonObject.set("metadata", jsonMetadataArray);

        return jsonObject;
    }

    void Object::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("bucket", jsonObject, bucket);
        Core::JsonUtils::GetJsonValueString("key", jsonObject, key);
        Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
        Core::JsonUtils::GetJsonValueLong("size", jsonObject, size);
        Core::JsonUtils::GetJsonValueString("md5sum", jsonObject, md5sum);
        Core::JsonUtils::GetJsonValueString("sha1sum", jsonObject, sha1sum);
        Core::JsonUtils::GetJsonValueString("sha256sum", jsonObject, sha256sum);
        Core::JsonUtils::GetJsonValueString("contentType", jsonObject, contentType);
        Core::JsonUtils::GetJsonValueString("internalName", jsonObject, internalName);
        Core::JsonUtils::GetJsonValueString("versionId", jsonObject, versionId);

        Poco::JSON::Array::Ptr jsonMetadataArray = jsonObject->getArray("metadata");
        for (int i = 0; i < jsonMetadataArray->size(); i++) {
            Poco::JSON::Object::Ptr jsonMetadataObject = jsonMetadataArray->getObject(i);
            std::string keyString = jsonMetadataObject->get("name");
            std::string valueString = jsonMetadataObject->get("value");
            metadata[keyString] = valueString;
        }
    }

    std::string Object::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Object &o) {
        os << "Object=" << bsoncxx::to_json(o.ToDocument());
        return os;
    }

}