//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_QUEUEATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SQS_QUEUEATTRIBUTE_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Database::Entity::SQS {

    struct QueueAttribute {

      /**
       * ID
       */
      long id = 0;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Delay seconds
       */
      int delaySeconds = 0;

      /**
       * Max message size (256kB)
       */
      int maxMessageSize = 262144;

      /**
       * Max retention period (4d)
       */
      int messageRetentionPeriod = 345600;

      /**
       * Policy
       *
       * <p>The queue's policy. A valid AWS policy.</p>
       */
      std::string policy;

      /**
       * Receive message timeout
       */
      int receiveMessageWaitTime = 20;

      /**
       * Visibility timeout
       */
      int visibilityTimeout = 30;

      /**
       * Redrive policy
       *
       * <p>JSON string</p>
       */
      std::string redrivePolicy;

      /**
       * Redrive allow policy
       *
       * <p>JSON string</p>
       */
      std::string redriveAllowPolicy;

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
      [[nodiscard]] Poco::MongoDB::Document::Ptr ToDocument() const {
          Poco::MongoDB::Document::Ptr queueAttributeDoc = new Poco::MongoDB::Document();
          queueAttributeDoc->add("queueUrl", queueUrl);
          queueAttributeDoc->add("delaySeconds", delaySeconds);
          queueAttributeDoc->add("maxMessageSize", maxMessageSize);
          queueAttributeDoc->add("messageRetentionPeriod", messageRetentionPeriod);
          queueAttributeDoc->add("policy", policy);
          queueAttributeDoc->add("receiveMessageWaitTime", receiveMessageWaitTime);
          queueAttributeDoc->add("visibilityTimeout", visibilityTimeout);
          queueAttributeDoc->add("redrivePolicy", redrivePolicy);
          queueAttributeDoc->add("redriveAllowPolicy", redriveAllowPolicy);
          queueAttributeDoc->add("created", created.timestamp());
          queueAttributeDoc->add("modified", modified.timestamp());
          return queueAttributeDoc;
      }

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
      friend std::ostream &operator<<(std::ostream &os, const QueueAttribute &r) {
          os << "QueueAttribute={id='" + std::to_string(r.id) + "' queueUrl='" + r.queueUrl + "' delaySeconds='" + std::to_string(r.delaySeconds) +
              "' maxMessageSize='" + std::to_string(r.maxMessageSize) + "' messageRetentionPeriod='" + std::to_string(r.messageRetentionPeriod) +
              "' policy='" + r.policy + "' receiveMessageWaitTime='" + std::to_string(r.receiveMessageWaitTime) + "' visibilityTimeout='"
              + std::to_string(r.visibilityTimeout) + "' redrivePolicy='" + r.redrivePolicy + "' redriveAllowPolicy='" + r.redriveAllowPolicy +
              "' created='" + Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct QueueAttribute QueueAttribute;
    typedef std::vector<QueueAttribute> QueueAttributeList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_QUEUEATTRIBUTE_H
