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
            kvp("contentType", contentType),
            kvp("metadata", metadataDoc),
            kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
            kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

        return objectDoc;
    }

    void Object::FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

        try {
            if (!mResult->empty()) {
                oid = mResult.value()["_id"].get_oid().value.to_string();
                region = mResult.value()["region"].get_string().value.to_string();
                bucket = mResult.value()["bucket"].get_string().value.to_string();
                key = mResult.value()["key"].get_string().value.to_string();
                owner = mResult.value()["owner"].get_string().value.to_string();
                size = mResult.value()["size"].get_int64().value;
                md5sum = mResult.value()["md5sum"].get_string().value.to_string();
                contentType = mResult.value()["contentType"].get_string().value.to_string();
                owner = mResult.value()["owner"].get_string().value.to_string();
                created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
                modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

                // Get metadata
                bsoncxx::document::view metadataView = mResult.value()["metadata"].get_document().value;
                for (bsoncxx::document::element metadataElement : metadataView) {
                    std::string key = metadataElement.key().to_string();
                    std::string value = metadataView[key].get_string().value.to_string();
                    metadata.emplace(key, value);
                }
            }
        } catch (mongocxx::exception::system_error &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void Object::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {
        try {
            if (!mResult->empty()) {
                oid = mResult.value()["_id"].get_oid().value.to_string();
                region = mResult.value()["region"].get_string().value.to_string();
                bucket = mResult.value()["bucket"].get_string().value.to_string();
                key = mResult.value()["key"].get_string().value.to_string();
                owner = mResult.value()["owner"].get_string().value.to_string();
                size = mResult.value()["size"].get_int64().value;
                md5sum = mResult.value()["md5sum"].get_string().value.to_string();
                contentType = mResult.value()["contentType"].get_string().value.to_string();
                owner = mResult.value()["owner"].get_string().value.to_string();
                created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
                modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

                // Get metadata
                bsoncxx::document::view metadataView = mResult.value()["metadata"].get_document().value;
                for (bsoncxx::document::element metadataElement : metadataView) {
                    std::string key = metadataElement.key().to_string();
                    std::string value = metadataView[key].get_string().value.to_string();
                    metadata.emplace(key, value);
                }
            }
        } catch (mongocxx::exception::system_error &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    std::string Object::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Object &o) {
        os << "Object={id='" << o.oid << "' bucket='" << o.bucket << "' key='" << o.key << "' owner='" << o.owner << "' size='" << std::to_string(o.size) <<
           "' md5sum='" << o.md5sum + "' contentType='" << o.contentType << " metadata={";
        for (const auto &t : o.metadata) {
            os << t.first << "=" << t.second << ", ";
        }
        os << '\b' << '\b';
        os << "}}";
        return os;
    }

}