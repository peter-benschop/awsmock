//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_LAMBDA_H
#define AWSMOCK_DB_ENTITY_LAMBDA_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Database::Entity::Lambda {

    struct Lambda {

      /**
       * ID
       */
      long id = 0;

      /**
       * Function
       */
      std::string function;

      /**
       * Runtime
       */
      std::string runtime;

      /**
       * Role
       */
      std::string role;

      /**
       * Handler
       */
      std::string handler;

      /**
       * Size
       */
      long size;

      /**
       * Image ID
       */
      std::string imageId;

      /**
       * Container ID
       */
      std::string containerId;

      /**
       * Tag
       */
      std::string tag;

      /**
       * ARN
       */
      std::string arn;

      /**
       * Last function start
       */
      Poco::DateTime lastStarted;

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
      friend std::ostream &operator<<(std::ostream &os, const Lambda &m) {
          os << "Lambda={id='" + std::to_string(m.id) + "' function='" + m.function + "'runtime='" + m.runtime + "' role='" + m.role + "' handler='" +
              m.handler + "' imageId='" + m.imageId + "' containerId='" + m.containerId + "' tag='" + m.tag + "' arn='" + m.arn +
              "' lastStarted='" + Poco::DateTimeFormatter().format(m.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' created='" + Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

}
#endif //AWSMOCK_DB_ENTITY_LAMBDA_H
