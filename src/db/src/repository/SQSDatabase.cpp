//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SQSDatabase.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    SQSDatabase::SQSDatabase() : _memoryDb(SQSMemoryDb::instance()), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _collectionNameQueue("sqs_queue"), _collectionNameMessage("sqs_message") {
    }

    bool SQSDatabase::QueueExists(const std::string &region, const std::string &name) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            int64_t count = _queueCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
            log_trace << "Queue exists: " << (count > 0 ? "true" : "false");
            return count > 0;

        } else {

            return _memoryDb.QueueExists(region, name);
        }
    }

    bool SQSDatabase::QueueUrlExists(const std::string &region, const std::string &queueUrl) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            int64_t count = _queueCollection.count_documents(make_document(kvp("region", region), kvp("queueUrl", queueUrl)));
            log_trace << "Queue exists: " << (count > 0 ? "true" : "false");
            return count > 0;

        } else {

            return _memoryDb.QueueUrlExists(region, queueUrl);
        }
    }

    bool SQSDatabase::QueueArnExists(const std::string &queueArn) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            int64_t count = _queueCollection.count_documents(make_document(kvp("queueArn", queueArn)));
            log_trace << "Queue exists: " << (count > 0 ? "true" : "false");
            return count > 0;

        } else {

            return _memoryDb.QueueArnExists(queueArn);
        }
    }

    Entity::SQS::Queue SQSDatabase::CreateQueue(const Entity::SQS::Queue &queue) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _queueCollection.insert_one(queue.ToDocument());
                log_trace << "Queue created, oid: " << result->inserted_id().get_oid().value.to_string();
                session.commit_transaction();

                return GetQueueById(result->inserted_id().get_oid().value);

            } catch (mongocxx::exception &e) {
                session.abort_transaction();
                log_error << "Collection transaction exception: " << e.what();
                throw Core::DatabaseException("Insert queue failed, region: " + queue.region + " queueUrl: " + queue.queueUrl + " message: " + e.what());
            }

        } else {

            return _memoryDb.CreateQueue(queue);
        }
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(bsoncxx::oid oid) {

        auto client = ConnectionPool::instance().GetConnection();
        mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("_id", oid)));
        if (mResult->empty()) {
            log_error << "Queue not found, oid: " << oid.to_string();
            throw Core::DatabaseException("Queue not found, oid: " + oid.to_string());
        }

        Entity::SQS::Queue result;
        result.FromDocument(mResult->view());
        return result;
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(const std::string &oid) {

        if (_useDatabase) {

            return GetQueueById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetQueueById(oid);
        }
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByArn(const std::string &queueArn) {

        Entity::SQS::Queue result;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("queueArn", queueArn)));

            if (mResult->empty()) {
                log_error << "Queue not found, queueArn: " << queueArn;
                throw Core::DatabaseException("Queue not found, queueArn: " + queueArn);
            }
            return result.FromDocument(mResult->view());


        } else {

            return _memoryDb.GetQueueByArn(queueArn);
        }
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByUrl(const std::string &region, const std::string &queueUrl) {

        Entity::SQS::Queue result;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("region", region), kvp("queueUrl", queueUrl)));
            if (!mResult) {

                log_error << "Queue not found, queueUrl: " << queueUrl;
                throw Core::DatabaseException("Queue not found, queueUrl: " + queueUrl);

            } else {

                return result.FromDocument(mResult->view());
            }

        } else {

            return _memoryDb.GetQueueByUrl(queueUrl);
        }
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByName(const std::string &region, const std::string &name) {

        Entity::SQS::Queue result;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
            if (!mResult) {

                log_info << "GetQueueByName succeeded, region: " << region << " name: " << name;
                return result.FromDocument(mResult->view());

            } else {

                log_warning << "GetQueueByName failed, region: " << region << " name: " << name;
                throw Core::DatabaseException("Queue not found, region: " + region + " name: " + name);
            }


        } else {

            return _memoryDb.GetQueueByName(region, name);
        }
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &region) {

        Entity::SQS::QueueList queueList;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            if (region.empty()) {

                auto queueCursor = _queueCollection.find({});
                for (auto queue: queueCursor) {
                    Entity::SQS::Queue result;
                    result.FromDocument(queue);
                    queueList.push_back(result);
                }

            } else {

                auto queueCursor = _queueCollection.find(make_document(kvp("region", region)));
                for (auto queue: queueCursor) {
                    Entity::SQS::Queue result;
                    result.FromDocument(queue);
                    queueList.push_back(result);
                }
            }

        } else {

            queueList = _memoryDb.ListQueues(region);
        }
        log_trace << "Got queue list, size: " << queueList.size();
        return queueList;
    }

    void SQSDatabase::PurgeQueue(const std::string &region, const std::string &queueUrl) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_many(make_document(kvp("region", region), kvp("queueUrl", queueUrl)));
                session.commit_transaction();
                log_debug << "Purged queue, count: " << result->deleted_count() << " url: " << queueUrl;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            log_debug << "Purged queue, count: " << _messages.size();
            _memoryDb.PurgeQueue(region, queueUrl);
        }
    }

    Entity::SQS::Queue SQSDatabase::UpdateQueue(Entity::SQS::Queue &queue) {

        if (_useDatabase) {

            mongocxx::options::find_one_and_update opts{};
            opts.return_document(mongocxx::options::return_document::k_after);

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto mResult =
                        _queueCollection.find_one_and_update(make_document(kvp("region", queue.region), kvp("name", queue.name)), queue.ToDocument(), opts);
                session.commit_transaction();
                log_trace << "Queue updated: " << queue.ToString();

                queue.FromDocument(mResult->view());
                return queue;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.UpdateQueue(queue);
        }
    }

    Entity::SQS::Queue SQSDatabase::CreateOrUpdateQueue(Entity::SQS::Queue &queue) {

        if (QueueUrlExists(queue.region, queue.queueUrl)) {

            return UpdateQueue(queue);

        } else {

            return CreateQueue(queue);
        }
    }

    long SQSDatabase::CountQueues(const std::string &region) {

        long count;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            if (region.empty()) {
                count = _queueCollection.count_documents({});
            } else {
                count = _queueCollection.count_documents(make_document(kvp("region", region)));
            }

        } else {

            return _memoryDb.CountQueues(region);
        }
        log_trace << "Count queues, result: " << count;
        return count;
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _queueCollection.delete_many(make_document(kvp("region", queue.region), kvp("queueUrl", queue.queueUrl)));
                session.commit_transaction();
                log_debug << "Queue deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteQueue(queue);
        }
    }

    void SQSDatabase::DeleteAllQueues() {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _queueCollection.delete_many({});
                session.commit_transaction();
                log_debug << "All queues deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteAllQueues();
        }
    }

    Entity::SQS::Message SQSDatabase::CreateMessage(const Entity::SQS::Message &message) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.insert_one(message.ToDocument());
                session.commit_transaction();
                log_trace << "Message created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetMessageById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.CreateMessage(message);
        }
    }

    bool SQSDatabase::MessageExists(const std::string &receiptHandle) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            int64_t count = messageCollection.count_documents(make_document(kvp("receiptHandle", receiptHandle)));
            log_trace << "Message exists: " << (count > 0 ? "true" : "false");
            return count > 0;

        } else {

            return _memoryDb.MessageExists(receiptHandle);
        }
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(bsoncxx::oid oid) {

        auto client = ConnectionPool::instance().GetConnection();
        auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = messageCollection.find_one(make_document(kvp("_id", oid)));
        Entity::SQS::Message result;
        result.FromDocument(mResult->view());

        return result;
    }

    Entity::SQS::Message SQSDatabase::GetMessageByReceiptHandle(const std::string &receiptHandle) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = messageCollection.find_one(make_document(kvp("receiptHandle", receiptHandle)));
            Entity::SQS::Message result;
            result.FromDocument(mResult->view());
            return result;

        } else {

            return _memoryDb.GetMessageByReceiptHandle(receiptHandle);
        }
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(const std::string &oid) {

        if (_useDatabase) {

            return GetMessageById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetMessageById(oid);
        }
    }

    Entity::SQS::Message SQSDatabase::UpdateMessage(Entity::SQS::Message &message) {

        if (_useDatabase) {

            mongocxx::options::find_one_and_update opts{};
            opts.return_document(mongocxx::options::return_document::k_after);

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto mResult = messageCollection.find_one_and_update(make_document(kvp("_id", bsoncxx::oid{message.oid})), message.ToDocument(), opts);
                session.commit_transaction();

                log_trace << "Message updated: " << ConvertMessageToJson(mResult.value());
                if (mResult) {
                    message.FromDocument(mResult->view());
                    return message;
                }

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.UpdateMessage(message);
        }
        return {};
    }

    Entity::SQS::Message SQSDatabase::CreateOrUpdateMessage(Entity::SQS::Message &message) {

        if (MessageExists(message.receiptHandle)) {

            return UpdateMessage(message);

        } else {

            return CreateMessage(message);
        }
    }

    Entity::SQS::MessageList SQSDatabase::ListMessages(const std::string &region) {

        Entity::SQS::MessageList messageList;
        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            if (region.empty()) {

                auto messageCursor = messageCollection.find({});
                for (auto message: messageCursor) {
                    Entity::SQS::Message result;
                    result.FromDocument(message);
                    messageList.push_back(result);
                }

            } else {

                auto messageCursor = messageCollection.find(make_document(kvp("region", region)));
                for (auto message: messageCursor) {
                    Entity::SQS::Message result;
                    result.FromDocument(message);
                    messageList.push_back(result);
                }
            }

        } else {

            messageList = _memoryDb.ListMessages(region);
        }
        log_trace << "Got message list, size: " << messageList.size();
        return messageList;
    }

    void SQSDatabase::ReceiveMessages(const std::string &region, const std::string &queueUrl, int visibility, int maxMessages, Entity::SQS::MessageList &messageList) {

        // First rest resources
        ResetMessages(queueUrl, visibility);

        auto reset = std::chrono::system_clock::now() + std::chrono::seconds(visibility);

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();

                mongocxx::options::find opts;
                opts.limit(maxMessages);

                // Get the cursor
                auto messageCursor = messageCollection.find(make_document(kvp("queueUrl", queueUrl),
                                                                          kvp("status",
                                                                              Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))),
                                                            opts);

                for (auto message: messageCursor) {

                    Entity::SQS::Message result;
                    result.FromDocument(message);

                    result.retries++;
                    result.receiptHandle = Core::AwsUtils::CreateSqsReceiptHandler();
                    messageList.push_back(result);

                    // Update values
                    messageCollection.update_one(make_document(kvp("_id", message["_id"].get_oid())),
                                                 make_document(kvp("$set",
                                                                   make_document(kvp("status",
                                                                                     Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INVISIBLE)),
                                                                                 kvp("reset", bsoncxx::types::b_date(reset)),
                                                                                 kvp("receiptHandle", result.receiptHandle),
                                                                                 kvp("retries", result.retries)))));
                }

                // Commit
                session.commit_transaction();

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            _memoryDb.ReceiveMessages(region, queueUrl, visibility, maxMessages, messageList);
        }
        log_trace << "Messages received, region: " << region << " queue: " << queueUrl + " count: " << messageList.size();
    }

    void SQSDatabase::ResetMessages(const std::string &queueUrl, long visibility) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.update_many(
                        make_document(
                                kvp("queueUrl", queueUrl),
                                kvp("status", Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INVISIBLE)),
                                kvp("reset", make_document(
                                                     kvp("$lt", bsoncxx::types::b_date(std::chrono::system_clock::now()))))),
                        make_document(kvp("$set",
                                          make_document(
                                                  kvp("status",
                                                      Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL)),
                                                  kvp("receiptHandle", ""),
                                                  kvp("reset", bsoncxx::types::b_null())))));
                session.commit_transaction();

                log_trace << "Message reset, updated: " << result->upserted_count() << " queue: " << queueUrl;

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            _memoryDb.ResetMessages(queueUrl, visibility);
        }
    }

    void SQSDatabase::RedriveMessages(const std::string &queueUrl, const Entity::SQS::RedrivePolicy &redrivePolicy) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                std::string dlqQueueUrl = Core::AwsUtils::ConvertSQSQueueArnToUrl(redrivePolicy.deadLetterTargetArn);
                auto result = messageCollection.update_many(make_document(kvp("queueUrl", queueUrl),
                                                                          kvp("status",
                                                                              Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL)),
                                                                          kvp("retries", make_document(
                                                                                                 kvp("$gt", redrivePolicy.maxReceiveCount)))),
                                                            make_document(kvp("$set", make_document(kvp("retries", 0),
                                                                                                    kvp("queueArn",
                                                                                                        redrivePolicy.deadLetterTargetArn),
                                                                                                    kvp("queueUrl",
                                                                                                        dlqQueueUrl)))));
                session.commit_transaction();
                log_trace << "Message redrive, arn: " << redrivePolicy.deadLetterTargetArn << " updated: "
                          << result->modified_count() << " queue: "
                          << queueUrl;

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            _memoryDb.RedriveMessages(queueUrl, redrivePolicy, Core::Configuration::instance());
        }
    }

    void SQSDatabase::ResetDelayedMessages(const std::string &queueUrl, long delay) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto now = std::chrono::system_clock::now();
                auto result = messageCollection.update_many(
                        make_document(
                                kvp("queueUrl", queueUrl),
                                kvp("status", Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::DELAYED)),
                                kvp("reset", make_document(
                                                     kvp("$lt", bsoncxx::types::b_date(now))))),
                        make_document(
                                kvp("$set",
                                    make_document(
                                            kvp("status", Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))))));
                session.commit_transaction();

                log_trace << "Delayed message reset, updated: " << result->upserted_count() << " queue: "
                          << queueUrl;

            } catch (mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Collection transaction exception: " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.ResetDelayedMessages(queueUrl, delay);
        }
    }

    void SQSDatabase::MessageRetention(const std::string &queueUrl, long retentionPeriod) {

        auto reset = std::chrono::system_clock::now() - std::chrono::seconds{retentionPeriod};

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_many(
                        make_document(
                                kvp("queueUrl", queueUrl),
                                kvp("created", make_document(
                                                       kvp("$lt", bsoncxx::types::b_date(reset))))));
                session.commit_transaction();

                log_trace << "Message retention reset, deleted: " << result->deleted_count() << " queue: " << queueUrl;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.MessageRetention(queueUrl, retentionPeriod);
        }
    }

    long SQSDatabase::CountMessages(const std::string &region, const std::string &queueUrl) {

        if (_useDatabase) {

            long count = 0;
            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            if (!region.empty() && !queueUrl.empty()) {
                count = static_cast<long>(messageCollection.count_documents(make_document(kvp("region", region), kvp("queueUrl", queueUrl))));
                log_trace << "Count resources, region: " << region << " url: " << queueUrl << " result: "
                          << count;
            } else if (!region.empty()) {
                count = static_cast<long>(messageCollection.count_documents(make_document(kvp("region", region))));
                log_trace << "Count resources, region: " << region << " result: " << count;
            } else {
                count = static_cast<long>(messageCollection.count_documents({}));
                log_trace << "Count resources, result: " << count;
            }
            return count;

        } else {

            return _memoryDb.CountMessages(region, queueUrl);
        }
    }

    long SQSDatabase::CountMessagesByStatus(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageStatus status) {

        if (_useDatabase) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

                long count = messageCollection.count_documents(make_document(kvp("region", region),
                                                                             kvp("queueUrl", queueUrl),
                                                                             kvp("status",
                                                                                 Entity::SQS::MessageStatusToString(status))));
                log_trace << "Count resources by status, status: " << Entity::SQS::MessageStatusToString(status) << " result: " << count;
                return count;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.CountMessagesByStatus(region, queueUrl, status);
        }
    }

    Entity::SQS::MessageWaitTime SQSDatabase::GetAverageMessageWaitingTime() {

        auto client = ConnectionPool::instance().GetConnection();
        auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

        try {
            mongocxx::pipeline p{};
            //p.match(make_document(kvp("queueName", queueName)));
            p.group(make_document(kvp("_id", "$queueName"),
                                  kvp("averageTime",
                                      make_document(kvp("$avg",
                                                        make_document(kvp("$subtract",
                                                                          make_array("$$NOW", "$created"))))))));
            p.project(make_document(kvp("_id", "$_id"), kvp("millis", make_document(kvp("$trunc", make_array("$averageTime", 2))))));

            Entity::SQS::MessageWaitTime waitTime;
            auto waitingTimeCursor = messageCollection.aggregate(p, mongocxx::options::aggregate{});
            for (const auto &waitingTime: waitingTimeCursor) {
                waitTime.waitTime[bsoncxx::string::to_string(waitingTime["_id"].get_string().value)] = waitingTime["millis"].get_double().value;
            }
            return waitTime;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    void SQSDatabase::DeleteMessages(const std::string &queueUrl) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_many(make_document(kvp("queueUrl", queueUrl)));
                session.commit_transaction();
                log_debug << "Messages deleted, queue: " << queueUrl << " count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteMessages(queueUrl);
        }
    }

    void SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_one(make_document(kvp("receiptHandle", message.receiptHandle)));
                session.commit_transaction();
                log_debug << "Messages deleted, receiptHandle: " << Core::StringUtils::SubString(message.receiptHandle, 0, 40) << "... count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteMessage(message);
        }
    }

    void SQSDatabase::DeleteMessage(const std::string &receiptHandle) {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_one(make_document(kvp("receiptHandle", receiptHandle)));
                session.commit_transaction();
                log_debug << "Messages deleted, receiptHandle: " << Core::StringUtils::SubString(receiptHandle, 0, 40) << "... count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteMessage(receiptHandle);
        }
    }

    void SQSDatabase::DeleteAllMessages() {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = messageCollection.delete_many({});
                session.commit_transaction();
                log_debug << "All resources deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteAllMessages();
        }
    }

    std::string SQSDatabase::ConvertMessageToJson(mongocxx::stdx::optional<bsoncxx::document::value> document) {
        return bsoncxx::to_json(document->view());
    }

}// namespace AwsMock::Database
