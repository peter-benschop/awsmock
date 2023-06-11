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

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>

namespace AwsMock::Database::Entity::SQS {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    struct QueueAttribute {

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
       * Receive message timeout
       */
      int receiveMessageWaitTime = 20;

      /**
       * Visibility timeout
       */
      int visibilityTimeout = 30;

      /**
       * Policy
       *
       * <p>The queue's policy. A valid AWS policy.</p>
       */
      std::string policy;

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
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const {

          view_or_value<view, value> queueAttributetDoc = make_document(
              kvp("delaySeconds", delaySeconds),
              kvp("maxMessageSize", maxMessageSize),
              kvp("messageRetentionPeriod", messageRetentionPeriod),
              kvp("policy", policy),
              kvp("receiveMessageWaitTime", receiveMessageWaitTime),
              kvp("visibilityTimeout", visibilityTimeout),
              kvp("redrivePolicy", redrivePolicy),
              kvp("redriveAllowPolicy", redriveAllowPolicy));

          return queueAttributetDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          delaySeconds = mResult.value()["delaySeconds"].get_int32().value;
          maxMessageSize = mResult.value()["maxMessageSize"].get_int32().value;
          messageRetentionPeriod = mResult.value()["messageRetentionPeriod"].get_int32().value;
          policy = mResult.value()["policy"].get_string().value.to_string();
          receiveMessageWaitTime = mResult.value()["receiveMessageWaitTime"].get_int32().value;
          visibilityTimeout = mResult.value()["visibilityTimeout"].get_int32().value;
          redrivePolicy = mResult.value()["redrivePolicy"].get_string().value.to_string();
          redriveAllowPolicy = mResult.value()["redriveAllowPolicy"].get_string().value.to_string();
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          delaySeconds = mResult.value()["delaySeconds"].get_int32().value;
          maxMessageSize = mResult.value()["maxMessageSize"].get_int32().value;
          messageRetentionPeriod = mResult.value()["messageRetentionPeriod"].get_int32().value;
          policy = mResult.value()["policy"].get_string().value.to_string();
          receiveMessageWaitTime = mResult.value()["receiveMessageWaitTime"].get_int32().value;
          visibilityTimeout = mResult.value()["visibilityTimeout"].get_int32().value;
          redrivePolicy = mResult.value()["redrivePolicy"].get_string().value.to_string();
          redriveAllowPolicy = mResult.value()["redriveAllowPolicy"].get_string().value.to_string();
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
          os << "QueueAttribute={delaySeconds='" << r.delaySeconds << "' maxMessageSize='" << r.maxMessageSize << "' messageRetentionPeriod='"
             << r.messageRetentionPeriod << "' policy='" << r.policy << "' receiveMessageWaitTime='" << r.receiveMessageWaitTime <<
             "' visibilityTimeout='" << r.visibilityTimeout << "' redrivePolicy='" << r.redrivePolicy << "' redriveAllowPolicy='" << r.redriveAllowPolicy << "'}";
          return os;
      }

    };

    typedef struct QueueAttribute QueueAttribute;
    typedef std::vector<QueueAttribute> QueueAttributeList;

    struct Queue {

      /**
       * ID
       */
      std::string oid;

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
       * Queue attributes
       */
      QueueAttribute attributes;

      /**
       * Creation date
       */
      Poco::DateTime created = Poco::DateTime();

      /**
       * Last modification date
       */
      Poco::DateTime modified = Poco::DateTime();

      /**
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const {

          view_or_value<view, value> queueDoc = make_document(
              kvp("region", region),
              kvp("name", name),
              kvp("owner", owner),
              kvp("queueUrl", queueUrl),
              kvp("queueArn", queueArn),
              kvp("attributes", attributes.ToDocument()),
              kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds()/1000))),
              kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds()/1000))));

          return queueDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          queueUrl = mResult.value()["queueUrl"].get_string().value.to_string();
          queueArn = mResult.value()["queueArn"].get_string().value.to_string();
          attributes.FromDocument(mResult.value()["attributes"].get_document().value);
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000000));
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          queueUrl = mResult.value()["queueUrl"].get_string().value.to_string();
          queueArn = mResult.value()["queueArn"].get_string().value.to_string();
          attributes.FromDocument(mResult.value()["attributes"].get_document().value);
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value)/1000000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value)/1000000));
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
      friend std::ostream &operator<<(std::ostream &os, const Queue &q) {
          os << "Queue={id='" << q.oid << "' region='" << q.region << "' name='" << q.name << "' owner='" << q.owner << "' queueUrl='" << q.queueUrl <<
             "' queueArn='" << q.queueArn << "' created='" << Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' modified='" << Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
          return os;
      }

    };

    typedef struct Queue Queue;
    typedef std::vector<Queue> QueueList;

} // namespace AwsMock::Database::Entity::S3
#endif // AWSMOCK_DB_ENTITY_SQS_QUEUE_H
