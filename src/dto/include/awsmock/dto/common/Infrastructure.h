//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H
#define AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H

// C++ standard includes
#include <string>
#include <utility>

// Poco includes
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/entity/cognito/User.h>
#include <awsmock/entity/cognito/UserPool.h>
#include <awsmock/entity/dynamodb/Item.h>
#include <awsmock/entity/dynamodb/Table.h>
#include <awsmock/entity/kms/Key.h>
#include <awsmock/entity/lambda/Lambda.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>
#include <awsmock/entity/secretsmanager/Secret.h>
#include <awsmock/entity/sns/Message.h>
#include <awsmock/entity/sns/Topic.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Dto::Common {

    /**
     * Infrastructure
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Infrastructure {

        /**
         * S3 buckets
         */
        Database::Entity::S3::BucketList s3Buckets;

        /**
         * S3 objects
         */
        Database::Entity::S3::ObjectList s3Objects;

        /**
         * SQS queues
         */
        Database::Entity::SQS::QueueList sqsQueues;

        /**
         * SQS messages
         */
        Database::Entity::SQS::MessageList sqsMessages;

        /**
         * SNS topics
         */
        Database::Entity::SNS::TopicList snsTopics;

        /**
         * SQS messages
         */
        Database::Entity::SNS::MessageList snsMessages;

        /**
         * Lambda functions
         */
        Database::Entity::Lambda::LambdaList lambdas;

        /**
         * Transfer servers
         */
        Database::Entity::Transfer::TransferList transferServers;

        /**
         * Cognito user pools
         */
        Database::Entity::Cognito::UserPoolList cognitoUserPools;

        /**
         * Cognito users
         */
        Database::Entity::Cognito::UserList cognitoUsers;

        /**
         * DynamoDb tables
         */
        Database::Entity::DynamoDb::TableList dynamoDbTables;

        /**
         * DynamoDb items
         */
        Database::Entity::DynamoDb::ItemList dynamoDbItems;

        /**
         * Secrets manager secrets
         */
        Database::Entity::SecretsManager::SecretList secrets;

        /**
         * Secrets manager secrets
         */
        Database::Entity::KMS::KeyList kmsKeys;

        /**
         * JSON representation
         *
         * @param prettyPrint pretty print, if true JSON indent=4
         * @return Infrastructure as JSON string
         */
        std::string ToJson(bool prettyPrint = false);

        /**
         * From JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_INFRASTRUCTURE_H
