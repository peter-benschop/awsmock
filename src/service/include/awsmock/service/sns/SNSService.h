//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SNS_SERVICE_H
#define AWSMOCK_SERVICE_SNS_SERVICE_H

// C++ standard includes
#include <chrono>
#include <ctime>
#include <string>

// Poco includes
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/sns/CreateTopicRequest.h>
#include <awsmock/dto/sns/CreateTopicResponse.h>
#include <awsmock/dto/sns/DeleteMessageRequest.h>
#include <awsmock/dto/sns/DeleteTopicResponse.h>
#include <awsmock/dto/sns/GetTopicAttributesRequest.h>
#include <awsmock/dto/sns/GetTopicAttributesResponse.h>
#include <awsmock/dto/sns/GetTopicDetailsRequest.h>
#include <awsmock/dto/sns/GetTopicDetailsResponse.h>
#include <awsmock/dto/sns/ListMessagesRequest.h>
#include <awsmock/dto/sns/ListMessagesResponse.h>
#include <awsmock/dto/sns/ListSubscriptionsByTopicRequest.h>
#include <awsmock/dto/sns/ListSubscriptionsByTopicResponse.h>
#include <awsmock/dto/sns/ListTopicsResponse.h>
#include <awsmock/dto/sns/PublishRequest.h>
#include <awsmock/dto/sns/PublishResponse.h>
#include <awsmock/dto/sns/SqsNotificationRequest.h>
#include <awsmock/dto/sns/SubscribeRequest.h>
#include <awsmock/dto/sns/SubscribeResponse.h>
#include <awsmock/dto/sns/TagResourceRequest.h>
#include <awsmock/dto/sns/TagResourceResponse.h>
#include <awsmock/dto/sns/UnsubscribeRequest.h>
#include <awsmock/dto/sns/UnsubscribeResponse.h>
#include <awsmock/dto/sns/mapper/Mapper.h>
#include <awsmock/dto/sqs/SendMessageRequest.h>
#include <awsmock/dto/sqs/SendMessageResponse.h>
#include <awsmock/repository/SNSDatabase.h>
#include <awsmock/service/sqs/SQSService.h>

#define SQS_PROTOCOL "sqs"
#define DEFAULT_SQS_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    /**
     * @brief SNS server thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSService {

      public:

        /**
         * @brief Constructor
         */
        explicit SNSService() : _snsDatabase(Database::SNSDatabase::instance()), _sqsDatabase(Database::SQSDatabase::instance()) {};

        /**
         * @brief Creates a new queue
         *
         * <p>In case the topic exists already, return the existing topic.</p>
         *
         * @param request create queue request
         * @return CreateQueueResponse
         */
        Dto::SNS::CreateTopicResponse CreateTopic(const Dto::SNS::CreateTopicRequest &request);

        /**
         * @brief Returns a list of all available queues
         *
         * @param region AWS region
         * @return ListQueuesResponse
         */
        Dto::SNS::ListTopicsResponse ListTopics(const std::string &region);

        /**
         * @brief Publish a message to a SNS topic
         *
         * @param request AWS region
         * @return PublishResponse
         */
        Dto::SNS::PublishResponse Publish(const Dto::SNS::PublishRequest &request);

        /**
         * @brief Subscribe to a topic
         *
         * @param request subscribe request DTO
         * @return SubscribeResponse DTO
         */
        Dto::SNS::SubscribeResponse Subscribe(const Dto::SNS::SubscribeRequest &request);

        /**
         * @brief Unsubscribe from a topic
         *
         * @param request unsubscribe request DTO
         * @return UnsubscribeResponse DTO
         */
        Dto::SNS::UnsubscribeResponse Unsubscribe(const Dto::SNS::UnsubscribeRequest &request);

        /**
         * @brief Sets tags for a topic
         *
         * @param request tag resource request DTO
         * @return TagResourceResponse DTO
         */
        Dto::SNS::TagResourceResponse TagResource(const Dto::SNS::TagResourceRequest &request);

        /**
         * @brief Returns the topic attributes
         *
         * @param request get topic attributes request DTO
         * @return GetTopicAttributesResponse DTO
         * @see GetTopicAttributesRequest
         * @see GetTopicAttributesResponse
         */
        Dto::SNS::GetTopicAttributesResponse GetTopicAttributes(const Dto::SNS::GetTopicAttributesRequest &request);

        /**
         * @brief Returns the topic details.
         *
         * @param request get topic details request DTO
         * @return GetTopicDetailsResponse DTO
         * @see GetTopicDetailsRequest
         * @see GetTopicDetailsResponse
         */
        Dto::SNS::GetTopicDetailsResponse GetTopicDetails(const Dto::SNS::GetTopicDetailsRequest &request);

        /**
         * Returns a list of subscriptions for a topic
         *
         * @param request list subscriptions request DTO
         * @return ListSubscriptionByTopicResponse DTO
         */
        Dto::SNS::ListSubscriptionsByTopicResponse ListSubscriptionsByTopic(const Dto::SNS::ListSubscriptionsByTopicRequest &request);

        /**
         * @brief Delete a queue
         *
         * @param region AWS region name
         * @param topicArn topic ARN
         * @return DeleteQueueResponse
         * @throws ServiceException
         */
        Dto::SNS::DeleteTopicResponse DeleteTopic(const std::string &region, const std::string &topicArn);

        /**
         * @brief List messages
         *
         * @param request list messages request
         * @return ListmessagesResponse
         * @see ListmessagesResponse
         * @throws ServiceException
         */
        Dto::SNS::ListMessagesResponse ListMessages(const Dto::SNS::ListMessagesRequest &request);

        /**
         * @brief Deletes a message
         *
         * @par
         * This is not an official AWS SDK service, but exists in AwsMock.
         *
         * @param request delete message request
         * @see DeleteMessageRequest
         * @throws ServiceException
         */
        void DeleteMessage(const Dto::SNS::DeleteMessageRequest &request);

      private:

        /**
         * @brief Checks the subscriptions.
         *
         * <p>If a SQS queue subscription is found send the message to the SQS queue.</p>
         */
        void CheckSubscriptions(const Dto::SNS::PublishRequest &request);

        /**
         * @brief Send a SNS message to an SQS queue
         *
         * @param subscription SNS subscription
         * @param request SNS publish request
         */
        void SendSQSMessage(const Database::Entity::SNS::Subscription &subscription, const Dto::SNS::PublishRequest &request);

        /**
         * SNS database connection
         */
        Database::SNSDatabase &_snsDatabase;

        /**
         * SQS database connection
         */
        Database::SQSDatabase &_sqsDatabase;

        /**
         * SQS module
         */
        SQSService _sqsService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SNS_SERVICE_H
