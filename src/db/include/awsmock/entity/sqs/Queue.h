//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_QUEUE_H
#define AWSMOCK_DB_ENTITY_SQS_QUEUE_H

// C++ includes
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>


// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/entity/sqs/QueueAttribute.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::SQS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * SQS queue entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
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
         * Queue userAttributes
         */
        QueueAttribute attributes;

        /**
         * Queue tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified;

        /**
         * Pagination token
         */
        std::string paginationToken;

        /**
         * Pagination score
         */
        double score;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        Entity::SQS::Queue FromDocument(std::optional<bsoncxx::document::view> mResult);

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
        void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

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
        friend std::ostream &operator<<(std::ostream &os, const Queue &q);
    };

    typedef std::vector<Queue> QueueList;

}// namespace AwsMock::Database::Entity::SQS

#endif// AWSMOCK_DB_ENTITY_SQS_QUEUE_H
