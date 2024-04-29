//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_H

// C++ includes
#include <chrono>
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock include
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/s3/BucketNotification.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::view_or_value;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    enum BucketVersionStatus {
        ENABLED,
        SUSPENDED,
        DISABLED
    };

    static std::map<BucketVersionStatus, std::string> BucketVersionStatusNames{
            {BucketVersionStatus::ENABLED, "enabled"},
            {BucketVersionStatus::SUSPENDED, "suspended"},
            {BucketVersionStatus::DISABLED, "disabled"},
    };

    [[maybe_unused]] static std::string BucketVersionStatusToString(BucketVersionStatus bucketVersionStatus) {
        return BucketVersionStatusNames[bucketVersionStatus];
    }

    [[maybe_unused]] static BucketVersionStatus BucketVersionStatusFromString(const std::string &bucketVersionStatus) {
        for (auto &it: BucketVersionStatusNames) {
            if (it.second == bucketVersionStatus) {
                return it.first;
            }
        }
        return BucketVersionStatus::DISABLED;
    }

    /**
     * S3 bucket entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Bucket {

        /**
         * ID
         */
        std::string oid;

        /**
         * Bucket region
         */
        std::string region;

        /**
         * Bucket name
         */
        std::string name;

        /**
         * Bucket owner
         */
        std::string owner;

        /**
         * Bucket notifications
         */
        std::vector<BucketNotification> notifications;

        /**
         * Bucket versioning state
         */
        BucketVersionStatus versionStatus = DISABLED;

        /**
         * Creation date
         */
        Poco::DateTime created;

        /**
         * Last modification date
         */
        Poco::DateTime modified;

        /**
         * Checks whether a notification with the given event name exists.
         *
         * @param eventName name of the event
         * @return true if notification with the given event name exists.
         */
        bool HasNotification(const std::string &eventName);

        /**
         * Returns a given notification by name
         *
         * @param eventName name of the event
         * @return found notification or notifications.end().
         */
        BucketNotification GetNotification(const std::string &eventName);

        /**
         * Returns a boolean indicating the versioinig state
         */
        [[nodiscard]] bool IsVersioned() const;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the entity to a JSON object
         *
         * @param jsonObject JSON object.
         */
        void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @param os output stream
         * @param bucket bucket entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Bucket &bucket);
    };

    typedef struct Bucket Bucket;
    typedef std::vector<Bucket> BucketList;

}// namespace AwsMock::Database::Entity::S3

#endif//AWSMOCK_DB_ENTITY_S3_BUCKET_H
