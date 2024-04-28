//
// Created by vogje01 on 01/06/2023.
//

#include "awsmock/utils/MongoUtils.h"
#include <awsmock/entity/kms/Key.h>

namespace AwsMock::Database::Entity::KMS {

    view_or_value<view, value> Key::ToDocument() const {

        auto tagsDoc = bsoncxx::builder::basic::document{};
        if (!tags.empty()) {
            for (const auto &t: tags) {
                tagsDoc.append(kvp(t.first, t.second));
            }
        }

        view_or_value<view, value> keyDoc = make_document(
                kvp("region", region),
                kvp("arn", arn),
                kvp("keyId", keyId),
                kvp("keyUsage", keyUsage),
                kvp("keySpec", keySpec),
                kvp("keyState", keyState),
                kvp("aes256Key", aes256Key),
                kvp("aes256Iv", aes256Iv),
                kvp("rsaPrivateKey", rsaPrivateKey),
                kvp("rsaPublicKey", rsaPublicKey),
                kvp("tags", tagsDoc),
                kvp("pendingWindowInDays", pendingWindowInDays),
                kvp("scheduledDeletion", MongoUtils::ToBson(scheduledDeletion)),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return keyDoc;
    }

    void Key::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
        keyId = bsoncxx::string::to_string(mResult.value()["keyId"].get_string().value);
        keyUsage = bsoncxx::string::to_string(mResult.value()["keyUsage"].get_string().value);
        keySpec = bsoncxx::string::to_string(mResult.value()["keySpec"].get_string().value);
        keyState = bsoncxx::string::to_string(mResult.value()["keyState"].get_string().value);
        aes256Key = bsoncxx::string::to_string(mResult.value()["aes256Key"].get_string().value);
        aes256Iv = bsoncxx::string::to_string(mResult.value()["aes256Iv"].get_string().value);
        rsaPrivateKey = bsoncxx::string::to_string(mResult.value()["rsaPrivateKey"].get_string().value);
        rsaPublicKey = bsoncxx::string::to_string(mResult.value()["rsaPublicKey"].get_string().value);
        pendingWindowInDays = mResult.value()["pendingWindowInDays"].get_int32().value;
        if (mResult.value()["scheduledDeletion"].type() != bsoncxx::type::k_null) {
            scheduledDeletion = MongoUtils::FromBson(mResult.value()["scheduledDeletion"].get_date());
        }
        created = MongoUtils::FromBson(mResult.value()["created"].get_date());
        modified = MongoUtils::FromBson(mResult.value()["modified"].get_date());

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
            for (bsoncxx::document::element tagElement: tagsView) {
                std::string key = bsoncxx::string::to_string(tagElement.key());
                std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                tags.emplace(key, value);
            }
        }
    }

    Poco::JSON::Object Key::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("arn", arn);
        jsonObject.set("keyId", keyId);
        jsonObject.set("keyUsage", keyUsage);
        jsonObject.set("keySpec", keySpec);
        jsonObject.set("keyState", keyState);
        jsonObject.set("aes256Key", aes256Key);
        jsonObject.set("aes256Iv", aes256Iv);
        jsonObject.set("rsaPrivateKey", rsaPrivateKey);
        jsonObject.set("rsaPublicKey", rsaPublicKey);
        jsonObject.set("pendingWindowInDays", pendingWindowInDays);
        if (scheduledDeletion.timestamp().epochTime() > 0) {
            jsonObject.set("scheduledDeletion", scheduledDeletion);
        }
        jsonObject.set("created", created);
        jsonObject.set("modified", modified);

        // Tags array
        if (!tags.empty()) {
            Poco::JSON::Array jsonTagArray;
            for (const auto &tag: tags) {
                Poco::JSON::Object jsonTagObject;
                jsonTagObject.set(tag.first, tag.second);
                jsonTagArray.add(jsonTagObject);
            }
            jsonObject.set("tags", jsonTagArray);
        }

        return jsonObject;
    }

    std::string Key::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Key &t) {
        os << "Key=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::KMS
