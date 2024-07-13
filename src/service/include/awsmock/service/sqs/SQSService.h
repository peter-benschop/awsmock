//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_SERVICE_H
#define AWSMOCK_SERVICE_SQS_SERVICE_H

// C++ standard includes
#include <chrono>
#include <map>
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Latin1Encoding.h>
#include <Poco/TextConverter.h>
#include <Poco/UTF8Encoding.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/core/monitoring/MetricServiceTimer.h>
#include <awsmock/dto/sqs/ChangeMessageVisibilityRequest.h>
#include <awsmock/dto/sqs/CreateQueueRequest.h>
#include <awsmock/dto/sqs/CreateQueueResponse.h>
#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>
#include <awsmock/dto/sqs/DeleteMessageRequest.h>
#include <awsmock/dto/sqs/DeleteMessageResponse.h>
#include <awsmock/dto/sqs/DeleteQueueRequest.h>
#include <awsmock/dto/sqs/DeleteQueueResponse.h>
#include <awsmock/dto/sqs/GetQueueAttributesRequest.h>
#include <awsmock/dto/sqs/GetQueueAttributesResponse.h>
#include <awsmock/dto/sqs/GetQueueUrlRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>
#include <awsmock/dto/sqs/ListQueueResponse.h>
#include <awsmock/dto/sqs/PurgeQueueRequest.h>
#include <awsmock/dto/sqs/ReceiveMessageRequest.h>
#include <awsmock/dto/sqs/ReceiveMessageResponse.h>
#include <awsmock/dto/sqs/SendMessageRequest.h>
#include <awsmock/dto/sqs/SendMessageResponse.h>
#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>
#include <awsmock/dto/sqs/SetQueueAttributesResponse.h>
#include <awsmock/dto/sqs/TagQueueRequest.h>
#include <awsmock/dto/sqs/model/EventNotification.h>
#include <awsmock/dto/sqs/model/EventRecord.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/lambda/LambdaService.h>

#define DEFAULT_USER "none"
#define DEFAULT_REGION "eu-central-1"
#define SQS_DEFAULT_ACCOUNT_ID "000000000000"
#define SQS_DEFAULT_VISIBILITY_TIMEOUT 300

namespace AwsMock::Service {

    using std::chrono::system_clock;

    /**
     * @brief SQS service
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSService {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSService() : _sqsDatabase(Database::SQSDatabase::instance()), _lambdaDatabase(Database::LambdaDatabase::instance()){};

        /**
         * @brief Creates a new queue.
         *
         * <p>In case the queue exists already, return the existing queue.</p>
         *
         * @param request create queue request
         * @return CreateQueueResponse
         */
        Dto::SQS::CreateQueueResponse CreateQueue(const Dto::SQS::CreateQueueRequest &request);

        /**
         * @brief Returns a list of all available queues
         *
         * @param region AWS region
         * @return ListQueuesResponse
         */
        Dto::SQS::ListQueueResponse ListQueues(const std::string &region);

        /**
         * @brief Purge a queue.
         *
         * @param request purge queue request
         * @throws ServiceException
         */
        void PurgeQueue(const Dto::SQS::PurgeQueueRequest &request);

        /**
         * @brief Return the queue userAttributes
         *
         * @param request get queue sqs request
         * @return GetQueueAttributesResponse
         * @throws ServiceException
         */
        Dto::SQS::GetQueueUrlResponse GetQueueUrl(const Dto::SQS::GetQueueUrlRequest &request);

        /**
         * @brief Return the queue userAttributes
         *
         * @param request get queue sqs request
         * @return GetQueueAttributesResponse
         * @throws ServiceException
         */
        Dto::SQS::GetQueueAttributesResponse GetQueueAttributes(const Dto::SQS::GetQueueAttributesRequest &request);

        /**
         * @brief Set queue userAttributes
         *
         * @param request put queue sqs request
         * @return SetQueueAttributesResponse
         * @throws ServiceException
         */
        Dto::SQS::SetQueueAttributesResponse SetQueueAttributes(Dto::SQS::SetQueueAttributesRequest &request);

        /**
         * @brief Sets the message visibility timeout timeout.
         *
         * @param request set visibility timeout request
         * @throws ServiceException
         */
        void SetVisibilityTimeout(Dto::SQS::ChangeMessageVisibilityRequest &request);

        /**
         * @brief Sets tags for a queue.
         *
         * <p>
         * Existing tags will be updates, and not existing tags will be created.
         * </p>
         *
         * @param request tag resource request DTO
         */
        void TagQueue(const Dto::SQS::TagQueueRequest &request);

        /**
         * @brief Delete a queue
         *
         * @param request delete request DTO
         * @return SQSQueueResponse
         * @throws ServiceException
         */
        Dto::SQS::DeleteQueueResponse DeleteQueue(const Dto::SQS::DeleteQueueRequest &request);

        /**
         * @brief Creates a new queue
         *
         * @param request create message request
         * @return SendMessageResponse
         * @throws ServiceException
         */
        Dto::SQS::SendMessageResponse SendMessage(const Dto::SQS::SendMessageRequest &request);

        /**
         * @brief Receive a list of resources
         *
         * @param request receive message request
         * @return ReceiveMessageResponse
         * @throws ServiceException
         */
        Dto::SQS::ReceiveMessageResponse ReceiveMessages(const Dto::SQS::ReceiveMessageRequest &request);

        /**
         * @brief Deletes a message
         *
         * @param request delete message request DTO
         * @throws ServiceException
         */
        void DeleteMessage(const Dto::SQS::DeleteMessageRequest &request);

        /**
         * @brief Deletes a message in a batch
         *
         * @param request delete message batch request DTO
         * @throws ServiceException
         */
        void DeleteMessageBatch(const Dto::SQS::DeleteMessageBatchRequest &request);

      private:

        /**
         * @brief Checks the attributes for a entry with 'all'. The search is case insensitive.
         *
         * @param lambda lambda to invoke.
         * @param message SQS message.
         * @param eventSourceArn event source ARN
         */
        void SendLambdaInvocationRequest(const Database::Entity::Lambda::Lambda &lambda, Database::Entity::SQS::Message &message, const std::string &eventSourceArn);

        /**
         * @brief Checks the attributes for a entry with 'all'. The search is case insensitive.
         *
         * @param attributes vector of attributes.
         * @param value value to check for.
         */
        static bool CheckAttribute(const std::vector<std::string> &attributes, const std::string &value);

        /**
         * SQS database connection
         */
        Database::SQSDatabase &_sqsDatabase;

        /**
         * Lambda database connection
         */
        Database::LambdaDatabase &_lambdaDatabase;

        /**
         * Lambda service
         */
        LambdaService _lambdaService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_SERVICE_H
