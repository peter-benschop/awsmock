//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_SQSDATABASE_H
#define AWSMOCK_DB_SQSDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/SQLite/Connector.h"

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Database {

    class SQSDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit SQSDatabase(const Core::Configuration &configuration);

      /**
       * Check existence of queue
       *
       * @param region AWS region
       * @param name queue name
       * @return true if queue already exists
       * @throws DatabaseException
       */
      bool QueueExists(const std::string &region, const std::string &name);

      /**
       * Check existence of queue
       *
       * @param url AWS region
       * @return true if queue already exists
       * @throws DatabaseException
       */
      bool QueueExists(const std::string &url);

      /**
       * Create a new queue in the SQS queue table
       *
       * @param queue queue entity
       * @return created SQS queue entity
       * @throws DatabaseException
       */
      Entity::SQS::Queue CreateQueue(const Entity::SQS::Queue& queue);

      /**
       * List all available queues
       *
       * @param region AWS region
       * @return List of SQS queues
       * @throws DatabaseException
       */
      Entity::SQS::QueueList ListQueues(const std::string &region);

      /**
       * Delete a queue.
       *
       * @param queue queue entity
       * @throws DatabaseException
       */
      void DeleteQueue(const Entity::SQS::Queue & queue);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif // AWSMOCK_DB_SQSDATABASE_H
