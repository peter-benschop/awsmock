//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SQSSERVICE_H
#define AWSMOCK_SERVICE_SQSSERVICE_H

// C++ standard includes
#include <string>
#include <chrono>
#include <ctime>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/TextConverter.h>
#include <Poco/Latin1Encoding.h>
#include <Poco/UTF8Encoding.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/sqs/CreateQueueRequest.h>
#include <awsmock/dto/sqs/CreateQueueResponse.h>
#include <awsmock/dto/sqs/GetQueueAttributesRequest.h>
#include <awsmock/dto/sqs/GetQueueAttributesResponse.h>
#include <awsmock/dto/sqs/DeleteMessageRequest.h>
#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>
#include <awsmock/dto/sqs/DeleteMessageResponse.h>
#include <awsmock/dto/sqs/DeleteQueueRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>
#include <awsmock/dto/sqs/ListQueueResponse.h>
#include <awsmock/dto/sqs/PurgeQueueRequest.h>
#include <awsmock/dto/sqs/ReceiveMessageRequest.h>
#include <awsmock/dto/sqs/ReceiveMessageResponse.h>
#include <awsmock/dto/sqs/SendMessageRequest.h>
#include <awsmock/dto/sqs/SendMessageResponse.h>
#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>
#include <awsmock/dto/sqs/ChangeMessageVisibilityRequest.h>
#include <awsmock/repository/SQSDatabase.h>

#define DEFAULT_ACCOUNT_ID "000000000000"
#define INTEGER_SIZE_IN_BYTES 4
#define STRING_TYPE_FIELD_INDEX '1'
#define BINARY_TYPE_FIELD_INDEX '2'
#define STRING_LIST_TYPE_FIELD_INDEX '3'
#define BINARY_LIST_TYPE_FIELD_INDEX '4'

namespace AwsMock::Service {

  class SQSService {

  public:

    /**
     * Constructor
     *
     * @param configuration module configuration
     * @param condition stop condition
     */
    explicit SQSService(Core::Configuration &configuration, Poco::Condition &condition);

    /**
     * Creates a new queue
     *
     * @param request create queue request
     * @return CreateQueueResponse
     */
    Dto::SQS::CreateQueueResponse CreateQueue(const Dto::SQS::CreateQueueRequest &request);

    /**
     * Returns a list of all available queues
     *
     * @param region AWS region
     * @return ListQueuesResponse
     */
    Dto::SQS::ListQueueResponse ListQueues(const std::string &region);

    /**
     * Purge a queue.
     *
     * @param request purge queue request
     * @throws ServiceException
     */
    void PurgeQueue(const Dto::SQS::PurgeQueueRequest &request);

    /**
     * Return the queue userAttributes
     *
     * @param request get queue sqs request
     * @return GetQueueAttributesResponse
     * @throws ServiceException
     */
    Dto::SQS::GetQueueUrlResponse GetQueueUrl(const Dto::SQS::GetQueueUrlRequest &request);

    /**
     * Return the queue userAttributes
     *
     * @param request get queue sqs request
     * @return GetQueueAttributesResponse
     * @throws ServiceException
     */
    Dto::SQS::GetQueueAttributesResponse GetQueueAttributes(const Dto::SQS::GetQueueAttributesRequest &request);

    /**
     * Set queue userAttributes
     *
     * @param request put queue sqs request
     * @throws ServiceException
     */
    void SetQueueAttributes(Dto::SQS::SetQueueAttributesRequest &request);

    /**
     * Sets the message visibilityTimeout timeout.
     *
     * @param request set visibilityTimeout timeout request
     * @throws ServiceException
     */
    void SetVisibilityTimeout(Dto::SQS::ChangeMessageVisibilityRequest &request);

    /**
     * Delete a queue
     *
     * @param request delete request DTO
     * @throws ServiceException
     */
    void DeleteQueue(const Dto::SQS::DeleteQueueRequest &request);

    /**
     * Creates a new queue
     *
     * @param request create message request
     * @return SendMessageResponse
     * @throws ServiceException
     */
    Dto::SQS::SendMessageResponse SendMessage(const Dto::SQS::SendMessageRequest &request);

    /**
     * Receive a list of messages
     *
     * @param request receive message request
     * @return ReceiveMessageResponse
     * @throws ServiceException
     */
    Dto::SQS::ReceiveMessageResponse ReceiveMessages(const Dto::SQS::ReceiveMessageRequest &request);

    /**
     * Deletes a message
     *
     * @param request delete message request DTO
     * @throws ServiceException
     */
    void DeleteMessage(const Dto::SQS::DeleteMessageRequest &request);

    /**
     * Deletes a message in a batch
     *
     * @param request delete message batch request DTO
     * @throws ServiceException
     */
    void DeleteMessageBatch(const Dto::SQS::DeleteMessageBatchRequest &request);

  private:

    /**
     * Returns the MD5 sum of the message body.
     *
     * @param body message body
     * @return MD5 sum of message body
     */
    std::string GetMd5Body(const std::string &body);

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Account ID
     */
    std::string _accountId;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Database connection
     */
    std::unique_ptr<Database::SQSDatabase> _database;

    /**
     * Shutdown condition
     */
    Poco::Condition &_condition;

    /**
     * Shutdown mutex
     */
    Poco::Mutex _mutex;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SQSSERVICE_H
