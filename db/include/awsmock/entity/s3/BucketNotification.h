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
      long id;

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
      long notificationId;

      /**
       * Function
       */
      std::string function;

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
          os << "BucketNotification={id='" + std::to_string(q.id) + "' region='" + q.region + "' notificationId='" + std::to_string(q.notificationId) +
              "' function='" + q.function + "' event='" + q.event + "' created='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct BucketNotification BucketNotification;

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
