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
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/s3/BucketEncryption.h>
#include <awsmock/entity/s3/BucketNotification.h>
#include <awsmock/entity/s3/LambdaNotification.h>
#include <awsmock/entity/s3/QueueNotification.h>
#include <awsmock/entity/s3/TopicNotification.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::view_or_value;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * @brief Versioning status
     */
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
     * @brief S3 bucket entity
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
         * AWS ARN
         */
        std::string arn;

        /**
         * Size in bytes
         */
        long size;

        /**
         * Number of object keys
         */
        long keys;

        /**
         * Bucket notifications
         */
        std::vector<BucketNotification> notifications;

        /**
         * Queue notification configurations
         */
        std::vector<QueueNotification> queueNotifications;

        /**
         * Topic notification configurations
         */
        std::vector<TopicNotification> topicNotifications;

        /**
         * Lambda notification configurations
         */
        std::vector<LambdaNotification> lambdaNotifications;

        /**
         * Bucket versioning state
         */
        BucketVersionStatus versionStatus = DISABLED;

        /**
         * Bucket encryption configurations
         */
        BucketEncryption bucketEncryption;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

        /**
         * @brief Checks whether a notification with the given event name exists.
         *
         * @param eventName name of the event
         * @return true if notification with the given event name exists.
         * @deprecated use HasQueueNotification,HasTopicNotification, HasLambdaNotification
         */
        bool HasNotification(const std::string &eventName);

        /**
         * @brief Checks whether a notification with the given ID exists.
         *
         * @param id other queue notification id.
         * @return true if notification with the given ID exists.
         */
        bool HasQueueNotificationId(const std::string &id);

        /**
         * @brief Checks whether a topic notification with the given ID exists.
         *
         * @param id other topic notification id.
         * @return true if notification with the given ID exists.
         */
        bool HasTopicNotificationId(const std::string &id);

        /**
         * @brief Checks whether a lambda notification with the given ID exists.
         *
         * @param id other lambda notification ID.
         * @return true if notification with the given ID exists.
         */
        bool HasLambdaNotificationId(const std::string &id);

        /**
         * @brief Checks whether a SQS queue notification with the given event name exists.
         *
         * @param eventName name of the event
         * @return true if notification with the given event name exists.
         */
        bool HasQueueNotification(const std::string &eventName);

        /**
         * @brief Checks whether a SNS topic notification with the given event name exists.
         *
         * @param eventName name of the event
         * @return true if notification with the given event name exists.
         */
        bool HasTopicNotification(const std::string &eventName);

        /**
         * @brief Checks whether a lambda notification with the given event name exists.
         *
         * @param eventName name of the event
         * @return true if notification with the given event name exists.
         */
        bool HasLambdaNotification(const std::string &eventName);

        /**
         * @brief Checks whether a the bucket has encryption enabled.
         *
         * @return true if encryption is enabled for the bucket.
         */
        bool HasEncryption() const;

        /**
         * @brief Returns a given notification by name
         *
         * @param eventName name of the event
         * @return found notification or notifications.end().
         * @deprecated use GetQueueNotification,GetTopicNotification, GetLambdaNotification
         */
        BucketNotification GetNotification(const std::string &eventName);

        /**
         * @brief Returns a given SQS queue notification by name
         *
         * @param eventName name of the event
         * @return found notification or notifications.end().
         */
        QueueNotification GetQueueNotification(const std::string &eventName);

        /**
         * @brief Returns a given SNS queue notification by name
         *
         * @param eventName name of the event
         * @return found notification or notifications.end().
         */
        TopicNotification GetTopicNotification(const std::string &eventName);

        /**
         * @brief Returns a given lambda notification by name
         *
         * @param eventName name of the event
         * @return found notification or notifications.end().
         */
        LambdaNotification GetLambdaNotification(const std::string &eventName);

        /**
         * @brief Returns a boolean indicating the versioinig state
         */
        [[nodiscard]] bool IsVersioned() const;

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts the entity to a JSON object
         *
         * @param jsonObject JSON object.
         */
        void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param bucket bucket entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Bucket &bucket);
    };

    typedef std::vector<Bucket> BucketList;

}// namespace AwsMock::Database::Entity::S3

#endif// AWSMOCK_DB_ENTITY_S3_BUCKET_H
