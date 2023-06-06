//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_LAMBDADATABASE_H
#define AWSMOCK_DB_LAMBDADATABASE_H

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
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/MessageAttribute.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/entity/sqs/QueueAttribute.h>

namespace AwsMock::Database {

    class LambdaDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit LambdaDatabase(const Core::Configuration &configuration);

      /**
       * Check existence of lambda
       *
       * @param region AWS region
       * @param name lambda name
       * @return true if lambda already exists
       * @throws DatabaseException
       */
      bool LambdaExists(const std::string &region, const std::string &name);

      bool CreateLambda(const std::string &region, const std::string &name);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif // AWSMOCK_DB_LAMBDADATABASE_H
