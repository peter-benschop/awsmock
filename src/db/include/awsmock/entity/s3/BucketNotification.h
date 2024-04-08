//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
#define AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H

// C++ includes
#include <string>
#include <chrono>
#include <sstream>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Database::Entity::S3 {

  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  /**
   * S3 bucket notification entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct BucketNotification {

    /**
     * Event
     */
    std::string event;

    /**
     * Notification ID
     */
    std::string notificationId;

    /**
     * Queue ARN
     */
    std::string queueArn;

    /**
     * lambda ARN
     */
    std::string lambdaArn;

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the entity to a JSON object
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Converts the entity to a JSON object
     *
     * @return DTO as string for logging.
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const BucketNotification &q);

  };

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
