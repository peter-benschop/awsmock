//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SNSSERVICE_H
#define AWSMOCK_SERVICE_SNSSERVICE_H

// C++ standard includes
#include <string>
#include <chrono>
#include <ctime>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/LogStream.h>

// AwsMock includes
#include "awsmock/core/CryptoUtils.h"
#include "awsmock/core/ServiceException.h"
#include "awsmock/core/AwsUtils.h"
#include "awsmock/dto/sns/CreateTopicRequest.h"
#include "awsmock/dto/sns/CreateTopicResponse.h"
#include "awsmock/dto/sns/ListTopicsResponse.h"
#include "awsmock/dto/sns/DeleteTopicResponse.h"
#include "awsmock/dto/sns/PublishRequest.h"
#include "awsmock/dto/sns/PublishResponse.h"
#include "awsmock/dto/sns/SubscribeRequest.h"
#include "awsmock/dto/sns/SubscribeResponse.h"
#include "awsmock/db/SNSDatabase.h"

#define DEFAULT_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    class SNSService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit SNSService(const Core::Configuration &configuration);

      /**
       * Creates a new queue
       *
       * @param request create queue request
       * @return CreateQueueResponse
       */
      Dto::SNS::CreateTopicResponse CreateTopic(const Dto::SNS::CreateTopicRequest &request);

      /**
       * Returns a list of all available queues
       *
       * @param region AWS region
       * @return ListQueuesResponse
       */
      Dto::SNS::ListTopicsResponse ListTopics(const std::string &region);

      /**
       * Publish a message to a SNS topic
       *
       * @param request AWS region
       * @return PublishResponse
       */
      Dto::SNS::PublishResponse Publish(const Dto::SNS::PublishRequest &request);

      /**
       * Publish a message to a SNS topic
       *
       * @param request AWS region
       * @return PublishResponse
       */
      Dto::SNS::SubscribeResponse Subscribe(const Dto::SNS::SubscribeRequest &request);

      /**
       * Delete a queue
       *
       * @param region AWS region name
       * @param topicArn topic ARN
       * @return DeleteQueueResponse
       * @throws ServiceException
       */
      Dto::SNS::DeleteTopicResponse DeleteTopic(const std::string &region, const std::string &topicArn);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * Logger
       */
      Poco::LogStream _logger;

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
      std::unique_ptr<Database::SNSDatabase> _database;
    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SNSSERVICE_H
