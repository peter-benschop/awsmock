//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_WORKER_H
#define AWSMOCK_SERVICE_DYNAMODB_WORKER_H

// Poco includes
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/dto/dynamodb/DescribeTableResponse.h>
#include <awsmock/dto/dynamodb/DynamoDbResponse.h>
#include <awsmock/dto/dynamodb/ListTableRequest.h>
#include <awsmock/dto/dynamodb/ListTableResponse.h>
#include <awsmock/repository/DynamoDbDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief DynamoDB worker thread
     *
     * Used as background thread to do maintenance work, like resetting synchronizing the dynamodb docker image with the database. The worker
     * is 'self-staring'.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbWorker {

      public:

        /**
         * @brief Constructor
         */
        explicit DynamoDbWorker();

        /**
         * @brief Synchronize tables.
         *
         * Loops over all DynamoDB tables an updates the MongoDB backend.
         */
        void SynchronizeTables();

      private:

        /**
         * Database connection
         */
        Database::DynamoDbDatabase &_dynamoDbDatabase = Database::DynamoDbDatabase::instance();

        /**
         * AWS region
         */
        std::string _region;

        /**
         * Docker host
         */
        std::string _dockerHost;

        /**
          * Docker port
          */
        int _dockerPort{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_DYNAMODB_WORKER_H
