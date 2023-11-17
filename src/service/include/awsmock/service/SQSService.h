//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SQSSERVICE_H
#define AWSMOCK_SERVICE_SQSSERVICE_H

// C++ standard includes
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

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
#include <awsmock/dto/sqs/DeleteQueueResponse.h>
#include <awsmock/dto/sqs/GetQueueUrlRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>
#include <awsmock/dto/sqs/ListQueueResponse.h>
#include <awsmock/dto/sqs/PurgeQueueRequest.h>
#include <awsmock/dto/sqs/PurgeQueueResponse.h>
#include <awsmock/dto/sqs/ReceiveMessageRequest.h>
#include <awsmock/dto/sqs/ReceiveMessageResponse.h>
#include <awsmock/dto/sqs/SendMessageRequest.h>
#include <awsmock/dto/sqs/SendMessageResponse.h>
#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>
#include <awsmock/dto/sqs/SetQueueAttributesResponse.h>
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
     * @param configuration service configuration
     * @param condition stop condition
     */
    explicit SQSService(const Core::Configuration &configuration, Poco::Condition &condition);

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
     * @return PurgeQueueResponse
     * @throws ServiceException
     */
    Dto::SQS::PurgeQueueResponse PurgeQueue(const Dto::SQS::PurgeQueueRequest &request);

    /**
     * Return the queue attributes
     *
     * @param request get queue sqs request
     * @return GetQueueAttributesResponse
     * @throws ServiceException
     */
    Dto::SQS::GetQueueUrlResponse GetQueueUrl(const Dto::SQS::GetQueueUrlRequest &request);

    /**
     * Return the queue attributes
     *
     * @param request get queue sqs request
     * @return GetQueueAttributesResponse
     * @throws ServiceException
     */
    Dto::SQS::GetQueueAttributesResponse GetQueueAttributes(const Dto::SQS::GetQueueAttributesRequest &request);

    /**
     * Put queue attributes
     *
     * @param request put queue sqs request
     * @return SetQueueAttributesResponse
     * @throws ServiceException
     */
    Dto::SQS::SetQueueAttributesResponse SetQueueAttributes(Dto::SQS::SetQueueAttributesRequest &request);

    /**
     * Sets the message visibility timeout.
     *
     * @param request set visibility timeout request
     * @throws ServiceException
     */
    void SetVisibilityTimeout(Dto::SQS::ChangeMessageVisibilityRequest &request);

    /**
     * Delete a queue
     *
     * @param request delete request DTO
     * @return DeleteQueueResponse
     * @throws ServiceException
     */
    Dto::SQS::DeleteQueueResponse DeleteQueue(const Dto::SQS::DeleteQueueRequest &request);

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

    /**
     * Returns the MD5 sum of all attributes.
     *
     * @param attributes vector of attributes
     * @return MD5 sum of attributes string
     */
    static std::string GetMd5Attributes(const Dto::SQS::MessageAttributeList &attributes);

  private:

    /**
     * Returns the MD5 sum of the message body.
     *
     * @param body message body
     * @return MD5 sum of message body
     */
    std::string GetMd5Body(const std::string &body);

    /**
     * Returns a integer as byte array and fill it in the given byte array at position offset.
     *
     * @param n integer value
     * @param bytes output byte array
     * @param offset offset of the output byte array
     */
    static void GetIntAsByteArray(int n, unsigned char *bytes, int offset);

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
    const Core::Configuration &_configuration;

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
