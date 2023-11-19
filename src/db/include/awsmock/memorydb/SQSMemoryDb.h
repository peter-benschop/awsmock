//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_SQSMEMORYDB_H
#define AWSMOCK_REPOSITORY_SQSMEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class SQSMemoryDb {

  public:

    /**
     * Constructor
     */
    SQSMemoryDb();

    /**
     * Singleton instance
     */
    static SQSMemoryDb &instance(void) {
      static Poco::SingletonHolder<SQSMemoryDb> sh;
      return *sh.get();
    }

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
     * @param region AWS region
     * @param queueUrl AWS region
     * @return true if queue already exists
     * @throws DatabaseException
     */
    bool QueueUrlExists(const std::string &region, const std::string &queueUrl);

    /**
     * Check existence of queue by ARN
     *
     * @param queueArn queue ARN
     * @return true in case queue exists
     * @throws DatabaseException
     */
    bool QueueArnExists(const std::string &queueArn);

    /**
     * Create a new queue in the SQS queue table
     *
     * @param queue queue entity
     * @return created SQS queue entity
     * @throws DatabaseException
     */
    Entity::SQS::Queue CreateQueue(const Entity::SQS::Queue &queue);

    /**
     * Returns a queue by primary key
     *
     * @param oid queue primary key
     * @return queue entity
     * @throws DatabaseException
     */
    Entity::SQS::Queue GetQueueById(const std::string &oid);

    /**
     * List all available queues
     *
     * @param region AWS region
     * @return List of SQS queues
     * @throws DatabaseException
     */
    Entity::SQS::QueueList ListQueues(const std::string &region = {});

    /**
     * Returns a queue by ARN
     *
     * @param queueArn queue ARN
     * @return queue entity
     * @throws DatabaseException
     */
    Entity::SQS::Queue GetQueueByArn(const std::string &queueArn);

    /**
     * Returns a queue by name and region
     *
     * @param region AWS region
     * @param queueName queue name
     * @return queue entity
     * @throws DatabaseException
     */
    Entity::SQS::Queue GetQueueByName(const std::string &region, const std::string &queueName);

    /**
     * Returns a queue by URL
     *
     * @param queueUrl queue URL
     * @return queue entity
     * @throws DatabaseException
     */
    Entity::SQS::Queue GetQueueByUrl(const std::string &queueUrl);

    /**
     * Purge a given queueUrl.
     *
     * @param region AWS region
     * @param queueUrl queueUrl name
     */
    void PurgeQueue(const std::string &region, const std::string &queueUrl);

    /**
     * Updates a given queue.
     *
     * @param queue AWS region
     * @return updated queue
     */
    Entity::SQS::Queue UpdateQueue(Entity::SQS::Queue &queue);

    /**
     * Count the number of queues for a given region.
     *
     * @param region AWS region
     * @return number of queues in the given region.
     */
    long CountQueues(const std::string &region = {});

    /**
     * Deletes a queue.
     *
     * @param queue queue entity
     * @throws DatabaseException
     */
    void DeleteQueue(const Entity::SQS::Queue &queue);

    /**
     * Deletes all queues
     */
    void DeleteAllQueues();

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * SQS queue vector, when running without database
     */
    std::map<std::string, Entity::SQS::Queue> _queues;

    /**
     * SQS message vector, when running without database
     */
    std::map<std::string, Entity::SQS::Message> _messages;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SQSMEMORYDB_H
