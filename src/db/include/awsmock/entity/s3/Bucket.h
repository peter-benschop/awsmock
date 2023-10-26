//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_H

// C++ includes
#include <string>
#include <chrono>
#include <sstream>
#include <map>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock include
#include <awsmock/entity/s3/BucketNotification.h>

namespace AwsMock::Database::Entity::S3 {

  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

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
    for (auto &it : BucketVersionStatusNames) {
      if (it.second == bucketVersionStatus) {
        return it.first;
      }
    }
    return BucketVersionStatus::DISABLED;
  }

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
     * Bucket versioning status
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
     * Returns a boolean indicating the versioinig status
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
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult);

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

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

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKET_H
