//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
#define AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::S3 {

    struct BucketNotification {

      /**
       * ID
       */
      long id = 0;

      /**
       * Bucket region
       */
      std::string region;

      /**
       * Bucket name
       */
      std::string bucket;

      /**
       * Notification ID
       */
      std::string notificationId;

      /**
       * Queue ARN
       */
      std::string queueArn;

      /**
       * Lambda ARN
       */
      std::string lambdaArn;

      /**
       * Event
       */
      std::string event;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;

      /**
       * Converts the DTO to a MongoDB document
       *
       * @return DTO as MongoDB document.
       */
/*      [[maybe_unused]] Poco::MongoDB::Document::Ptr ToDocument() {
          Poco::MongoDB::Document::Ptr bucketNotificationDoc = new Poco::MongoDB::Document();
          bucketNotificationDoc->add("region", region);
          bucketNotificationDoc->add("bucket", bucket);
          bucketNotificationDoc->add("notificationId", notificationId);
          bucketNotificationDoc->add("queueArn", queueArn);
          bucketNotificationDoc->add("lambdaArn", lambdaArn);
          bucketNotificationDoc->add("event", event);
          bucketNotificationDoc->add("created", created.timestamp());
          bucketNotificationDoc->add("modified", modified.timestamp());
          return bucketNotificationDoc;
      };*/

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const BucketNotification &q) {
          os << "BucketNotification={id='" + std::to_string(q.id) + "' region='" + q.region + "' notificationId='" + q.notificationId + "' queueArn='" + q.queueArn +
              "' lambdaArn='" + q.lambdaArn + "' event='" + q.event + "' created='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct BucketNotification BucketNotification;

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
