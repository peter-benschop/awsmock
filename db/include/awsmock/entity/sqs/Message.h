//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>

// AwsMock includes
#include "Attribute.h"

namespace AwsMock::Database::Entity::SQS {

    enum STATUS { CREATED, SEND, RESEND };

    struct Message {

      /**
       * ID
       */
      long id;

      /**
       * Queue name
       */
      std::string queue;

      /**
       * Message body
       */
      std::string body;

      /**
       * Status
       */
      int status = CREATED;

      /**
       * Last send datetime
       */
      Poco::DateTime lastSend;

      /**
       * Send retries
       */
      int retries = 0;

      /**
       * Message ID
       */
      std::string messageId;

      /**
       * Receipt handle
       */
      std::string receiptHandle;

      /**
       * MD5 sum body
       */
      std::string md5Body;

      /**
       * MD5 sum attributes
       */
      std::string md5Attr;

      /**
       * List of attributes
       */
      AttributeList attributeList;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;
    };

    typedef struct Message Message;
    typedef std::vector<Message> MessageList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
