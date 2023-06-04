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

    };

    typedef struct BucketNotification BucketNotification;

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKETNOTIFICATION_H
