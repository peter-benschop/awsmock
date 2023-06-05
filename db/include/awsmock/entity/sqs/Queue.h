//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_QUEUE_H
#define AWSMOCK_DB_ENTITY_SQS_QUEUE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::SQS {

    struct Queue {

      /**
       * ID
       */
      long id = 0;

      /**
       * AWS region
       */
      std::string region;

      /**
       * Queue name
       */
      std::string name;

      /**
       * Owner
       */
      std::string owner;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Queue ARN
       */
      std::string queueArn;

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
      friend std::ostream &operator<<(std::ostream &os, const Queue &q) {
          os << "Queue={id='" + std::to_string(q.id) + "' region='" + q.region + "' name='" + q.name + "' owner='" + q.owner + "' queueUrl='" + q.queueUrl +
          "' queueArn='" + q.queueArn + "' created='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct Queue Queue;
    typedef std::vector<Queue> QueueList;

} // namespace AwsMock::Database::Entity::S3
#endif // AWSMOCK_DB_ENTITY_SQS_QUEUE_H
