//
// Created by vogje01 on 12/10/23.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_TOPIC_ATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SNS_TOPIC_ATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/JSON/Parser.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/entity/sqs/RedrivePolicy.h>

namespace AwsMock::Database::Entity::SNS {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    /**
     * SNS topic attribute entity
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct TopicAttribute {

        /**
         * Delivery policy
         *
         * <p>
         * The policy that defines how Amazon SNS retries failed deliveries to HTTP/S endpoints.
         * </p>
         */
        std::string deliveryPolicy;

        /**
         * Display name.
         *
         * <p>
         * The display name to use for a topic with SMS subscriptions.
         * </p>
         */
        std::string displayName;

        /**
         * FIFO topic
         *
         * <p>
         * Set to true to create a FIFO topic.
         * </p>
         */
        bool fifoTopic = false;

        /**
         * Policy
         *
         * <p>
         * The policy that defines who can access your topic. By default, only the topic owner can publish or subscribe to
         * the topic.
         * </p>
         */
        std::string policy;

        /**
         * Signature version
         *
         * <p>
         * The signature version corresponds to the hashing algorithm used while creating the signature of the notifications,
         * subscription confirmations, or unsubscribe confirmation messages sent by Amazon SNS. By default, SignatureVersion
         * is set to 1.
         * <p>
         */
        std::string signatureVersion;

        /**
         * Tracing config
         *
         * <p>
         * Tracing mode of an Amazon SNS topic. By default TracingConfig is set to PassThrough, and the topic passes through
         * the tracing header it receives from an Amazon SNS publisher to its subscriptions. If set to Active, Amazon SNS
         * will vend X-Ray segment data to topic owner account if the sampled flag in the tracing header is true. This is
         * only supported on standard topics.
         * <p>
         */
        std::string tracingConfig;

        /**
         * KMS master key ID
         *
         * <p>
         * The ID of an AWS managed customer master key (CMK) for Amazon SNS or a custom CMK. For more information, see
         * Key Terms. For more examples, see KeyId in the AWS Key Management Service API Reference.
         * </p>
         */
        std::string kmsMasterKeyId;

        /**
         * Archiving policy.
         *
         * <p>
         * Adds or updates an inline policy document to archive messages stored in the specified Amazon SNS topic.
         * </p>
         */
        std::string archivePolicy;

        /**
         * Beginning archive time.
         *
         * <p>
         * The earliest starting point at which a message in the topic’s archive can be replayed from. This point in time
         * is based on the configured message retention period set by the topic’s message archiving policy.
         * </p>
         */
        Poco::DateTime beginningArchiveTime;

        /**
         * Content based deduplication.
         *
         * <p>
         * Enables content-based deduplication for FIFO topics.
         * </p>
         */
        bool contentBasedDeduplication = false;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value <view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document view.
         */
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the entity to a JSON object
         *
         * @param jsonObject JSON object
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
         * @param os output stream
         * @param r queue attribute
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const TopicAttribute &r);

    };

} // namespace AwsMock::Database::Entity::SQS

#endif // AWSMOCK_DB_ENTITY_SNS_TOPIC_ATTRIBUTE_H
