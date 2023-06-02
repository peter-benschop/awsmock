//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SQSSERVICE_H
#define AWSMOCK_SERVICE_SQSSERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Node.h"

// AwsMock includes
#include "awsmock/core/CryptoUtils.h"
#include "awsmock/core/ServiceException.h"
#include "awsmock/dto/sqs/ListQueueResponse.h"
#include "awsmock/dto/sqs/CreateMessageRequest.h"
#include "awsmock/dto/sqs/CreateMessageResponse.h"
#include "awsmock/dto/sqs/CreateQueueRequest.h"
#include "awsmock/dto/sqs/CreateQueueResponse.h"
#include "awsmock/dto/sqs/DeleteQueueRequest.h"
#include "awsmock/dto/sqs/DeleteQueueResponse.h"
#include "awsmock/dto/sqs/PurgeQueueRequest.h"
#include "awsmock/dto/sqs/PurgeQueueResponse.h"
#include "awsmock/db/SQSDatabase.h"

namespace AwsMock::Service {

    class SQSService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit SQSService(const Core::Configuration &configuration);

      /**
       * Creates a new queue
       *
       * @param region AWS region
       * @param region AWS region
       * @return CreateQueueResponse
       */
      Dto::SQS::CreateQueueResponse CreateQueue(const Dto::SQS::CreateQueueRequest & request);

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
       * @param region AWS region
       * @param queueUrl queue URL
       * @return PurgeQueueResponse
       * @throws ServiceException
       */
      Dto::SQS::PurgeQueueResponse PurgeQueue(const Dto::SQS::PurgeQueueRequest &request);

      /**
       * Creates a new queue
       *
       * @param region AWS region
       * @param region AWS region
       * @return CreateQueueResponse
       */
      Dto::SQS::CreateMessageResponse CreateMessage(const Dto::SQS::CreateMessageRequest &request);

      /**
       * Delete a queue
       *
       * @param request delete request DTO
       * @return DeleteQueueResponse
       */
      Dto::SQS::DeleteQueueResponse DeleteQueue(const Dto::SQS::DeleteQueueRequest &request);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Database connection
       */
      std::unique_ptr<Database::SQSDatabase> _database;
    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SQSSERVICE_H
