//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SQSDatabase.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    SQSDatabase::SQSDatabase() : _databaseName(GetDatabaseName()), _collectionNameQueue("sqs_queue"), _collectionNameMessage("sqs_message"), _memoryDb(SQSMemoryDb::instance()) {
    }

    bool SQSDatabase::QueueExists(const std::string &region, const std::string &name) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            const int64_t count = _queueCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
            log_trace << "Queue exists: " << std::boolalpha << count;
            return count > 0;
        }
        return _memoryDb.QueueExists(region, name);
    }

    bool SQSDatabase::QueueUrlExists(const std::string &region, const std::string &queueUrl) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            document query;
            if (!region.empty()) {
                query.append(kvp("region", region));
            }
            if (!queueUrl.empty()) {
                query.append(kvp("queueUrl", queueUrl));
            }

            const int64_t count = _queueCollection.count_documents(query.extract());
            log_trace << "Queue exists: " << std::boolalpha << count;
            return count > 0;
        }
        return _memoryDb.QueueUrlExists(region, queueUrl);
    }

    bool SQSDatabase::QueueArnExists(const std::string &queueArn) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            const int64_t count = _queueCollection.count_documents(make_document(kvp("queueArn", queueArn)));
            log_trace << "Queue exists: " << std::boolalpha << count;
            return count > 0;
        }
        return _memoryDb.QueueArnExists(queueArn);
    }

    Entity::SQS::Queue SQSDatabase::CreateQueue(Entity::SQS::Queue &queue) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = _queueCollection.insert_one(queue.ToDocument());
                log_trace << "Queue created, oid: " << result->inserted_id().get_oid().value.to_string();
                session.commit_transaction();

                queue.oid = result->inserted_id().get_oid().value.to_string();
                return queue;

            } catch (mongocxx::exception &e) {
                session.abort_transaction();
                log_error << "Collection transaction exception: " << e.what();
                throw Core::DatabaseException("Insert queue failed, region: " + queue.region + " queueUrl: " + queue.queueUrl + " message: " + e.what());
            }
        }
        return _memoryDb.CreateQueue(queue);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(bsoncxx::oid oid) const {

        const auto client = ConnectionPool::instance().GetConnection();
        mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

        const std::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("_id", oid)));
        if (mResult->empty()) {
            log_error << "Queue not found, oid: " << oid.to_string();
            throw Core::DatabaseException("Queue not found, oid: " + oid.to_string());
        }

        Entity::SQS::Queue result;
        result.FromDocument(mResult->view());
        return result;
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(const std::string &oid) const {

        if (HasDatabase()) {

            return GetQueueById(bsoncxx::oid(oid));
        }
        return _memoryDb.GetQueueById(oid);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByArn(const std::string &queueArn) const {

        if (HasDatabase()) {
            Entity::SQS::Queue result;

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            const auto mResult = _queueCollection.find_one(make_document(kvp("queueArn", queueArn)));

            if (!mResult) {
                log_error << "Queue not found, queueArn: " << queueArn;
                throw Core::DatabaseException("Queue not found, queueArn: " + queueArn);
            }
            return result.FromDocument(mResult->view());
        }
        return _memoryDb.GetQueueByArn(queueArn);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByUrl(const std::string &region, const std::string &queueUrl) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            document query;
            if (!region.empty()) {
                query.append(kvp("region", region));
            }
            if (!queueUrl.empty()) {
                query.append(kvp("queueUrl", queueUrl));
            }
            if (const auto mResult = _queueCollection.find_one(query.extract()); !mResult) {
                log_error << "Queue not found, region: " << region << " queueUrl: " << queueUrl;
                throw Core::DatabaseException("Queue not found, region: " + region + " queueUrl: " + queueUrl);
            } else {
                Entity::SQS::Queue result;
                return result.FromDocument(mResult->view());
            }
        }
        return _memoryDb.GetQueueByUrl(queueUrl);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueByName(const std::string &region, const std::string &queueName) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            document query;
            if (!region.empty()) {
                query.append(kvp("region", region));
            }
            if (!queueName.empty()) {
                query.append(kvp("queueName", queueName));
            }

            if (const std::optional<value> mResult = _queueCollection.find_one(query.extract()); !mResult) {

                log_warning << "GetQueueByName failed, region: " << region << " name: " << queueName;
                throw Core::DatabaseException("Queue not found, region: " + region + " name: " + queueName);

            } else {
                Entity::SQS::Queue result;
                log_info << "GetQueueByName succeeded, region: " << region << " name: " << queueName;
                return result.FromDocument(mResult->view());
            }


        } else {

            return _memoryDb.GetQueueByName(region, queueName);
        }
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &prefix, int pageSize, int pageIndex, const std::vector<Core::SortColumn> &sortColumns, const std::string &region) const {

        Entity::SQS::QueueList queueList;
        if (HasDatabase()) {

            mongocxx::options::find opts;

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            document query = {};
            if (!prefix.empty()) {
                query.append(kvp("name", make_document(kvp("$regex", "^" + prefix))));
            }
            if (!region.empty()) {
                query.append(kvp("region", region));
            }

            if (pageSize > 0) {
                opts.limit(pageSize);
            }
            if (pageIndex > 0) {
                opts.skip(pageIndex * pageSize);
            }

            opts.sort(make_document(kvp("_id", 1)));
            if (!sortColumns.empty()) {
                document sort;
                for (const auto &[column, sortDirection]: sortColumns) {
                    sort.append(kvp(column, sortDirection));
                }
                opts.sort(sort.extract());
            }

            for (auto queueCursor = _queueCollection.find(query.view(), opts); auto queue: queueCursor) {
                Entity::SQS::Queue result;
                result.FromDocument(queue);
                queueList.push_back(result);
            }

        } else {

            queueList = _memoryDb.ListQueues(region);
        }
        log_trace << "Got queue list, size: " << queueList.size();
        return queueList;
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &region) const {

        Entity::SQS::QueueList queueList;
        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            bsoncxx::builder::basic::document query = {};
            if (!region.empty()) {
                query.append(kvp("region", region));
            }

            for (auto queueCursor = _queueCollection.find(query.view()); auto queue: queueCursor) {
                Entity::SQS::Queue result;
                result.FromDocument(queue);
                queueList.push_back(result);
            }

        } else {

            queueList = _memoryDb.ListQueues(region);
        }
        log_trace << "Got queue list, size: " << queueList.size();
        return queueList;
    }

    void SQSDatabase::PurgeQueue(const std::string &queueArn) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_many(make_document(kvp("queueArn", queueArn)));
                session.commit_transaction();
                log_debug << "Purged queue, count: " << result->deleted_count() << " queueArn: " << queueArn;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            log_debug << "Purged queue, count: " << _messages.size();
            _memoryDb.PurgeQueue(queueArn);
        }
    }

    Entity::SQS::Queue SQSDatabase::UpdateQueue(Entity::SQS::Queue &queue) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                queue.modified = system_clock::now();
                const auto mResult = _queueCollection.find_one_and_update(make_document(kvp("region", queue.region), kvp("name", queue.name)), queue.ToDocument());
                session.commit_transaction();
                log_trace << "Queue updated: " << queue.ToString();

                if (mResult) {
                    queue.FromDocument(mResult->view());
                    return queue;
                }

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.UpdateQueue(queue);
        }
        return {};
    }

    Entity::SQS::Queue SQSDatabase::CreateOrUpdateQueue(Entity::SQS::Queue &queue) const {

        if (QueueUrlExists(queue.region, queue.queueUrl)) {

            return UpdateQueue(queue);

        } else {

            return CreateQueue(queue);
        }
    }

    long SQSDatabase::CountQueues(const std::string &prefix, const std::string &region) const {

        long count;
        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];

            bsoncxx::builder::basic::document query = {};
            if (!prefix.empty()) {
                query.append(kvp("name", make_document(kvp("$regex", "^" + prefix))));
            }

            if (!region.empty()) {
                query.append(kvp("region", region));
            }

            count = _queueCollection.count_documents(query.extract());

        } else {

            return _memoryDb.CountQueues(prefix, region);
        }
        log_trace << "Count queues, result: " << count;
        return count;
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = _queueCollection.delete_many(make_document(kvp("region", queue.region), kvp("queueUrl", queue.queueUrl)));
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

    void SQSDatabase::DeleteAllQueues() const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = _queueCollection.delete_many({});
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

    Entity::SQS::Message SQSDatabase::CreateMessage(Entity::SQS::Message &message) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.insert_one(message.ToDocument());
                session.commit_transaction();
                log_trace << "Message created, oid: " << result->inserted_id().get_oid().value.to_string();

                message.oid = result->inserted_id().get_oid().value.to_string();
                return message;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.CreateMessage(message);
        }
    }

    bool SQSDatabase::MessageExists(const std::string &receiptHandle) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            try {

                const int64_t count = messageCollection.count_documents(make_document(kvp("receiptHandle", receiptHandle)));
                log_trace << "Message exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.MessageExists(receiptHandle);
        }
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(bsoncxx::oid oid) const {

        const auto client = ConnectionPool::instance().GetConnection();
        auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

        std::optional<bsoncxx::document::value> mResult = messageCollection.find_one(make_document(kvp("_id", oid)));
        Entity::SQS::Message result;
        result.FromDocument(mResult->view());

        return result;
    }

    Entity::SQS::Message SQSDatabase::GetMessageByReceiptHandle(const std::string &receiptHandle) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            if (std::optional<bsoncxx::document::value> mResult = messageCollection.find_one(make_document(kvp("receiptHandle", receiptHandle)))) {
                Entity::SQS::Message result;
                result.FromDocument(mResult->view());
                return result;
            }

        } else {

            return _memoryDb.GetMessageByReceiptHandle(receiptHandle);
        }
        return {};
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(const std::string &oid) const {

        if (HasDatabase()) {

            return GetMessageById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetMessageById(oid);
        }
    }

    Entity::SQS::Message SQSDatabase::UpdateMessage(Entity::SQS::Message &message) const {

        if (HasDatabase()) {

            mongocxx::options::find_one_and_update opts{};
            opts.return_document(mongocxx::options::return_document::k_after);

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                message.modified = system_clock::now();
                const auto mResult = messageCollection.find_one_and_update(make_document(kvp("_id", bsoncxx::oid{message.oid})), message.ToDocument(), opts);
                session.commit_transaction();

                if (mResult) {
                    message.FromDocument(mResult->view());
                    log_trace << "Message updated: " << message.ToString();
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

    Entity::SQS::Message SQSDatabase::CreateOrUpdateMessage(Entity::SQS::Message &message) const {

        if (MessageExists(message.receiptHandle)) {

            return UpdateMessage(message);

        } else {

            return CreateMessage(message);
        }
    }

    Entity::SQS::MessageList SQSDatabase::ListMessages(const std::string &region) const {

        Entity::SQS::MessageList messageList;
        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            bsoncxx::builder::basic::document query;
            if (!region.empty()) {
                query.append(kvp("region", region));
            }

            for (auto messageCursor = messageCollection.find(query.extract()); auto &message: messageCursor) {
                Entity::SQS::Message result;
                result.FromDocument(message);
                messageList.push_back(result);
            }

        } else {

            messageList = _memoryDb.ListMessages(region);
        }
        log_trace << "Got message list, size: " << messageList.size();
        return messageList;
    }

    Entity::SQS::MessageList SQSDatabase::ListMessages(const std::string &queueArn, const std::string &prefix, int pageSize, int pageIndex, const std::vector<Core::SortColumn> &sortColumns) const {

        Entity::SQS::MessageList messageList;
        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            mongocxx::options::find opts;
            if (pageSize > 0) {
                opts.limit(pageSize);
                if (pageIndex > 0) {
                    opts.skip(pageSize * pageIndex);
                }
            }
            opts.sort(make_document(kvp("_id", 1)));
            if (!sortColumns.empty()) {
                bsoncxx::builder::basic::document sort;
                for (const auto &[column, sortDirection]: sortColumns) {
                    sort.append(kvp(column, sortDirection));
                }
                opts.sort(sort.extract());
            }

            bsoncxx::builder::basic::document query = {};
            if (!prefix.empty()) {
                query.append(kvp("name", make_document(kvp("$regex", "^" + prefix))));
            }

            if (!queueArn.empty()) {
                query.append(kvp("queueArn", queueArn));
            }

            for (auto messageCursor = messageCollection.find(query.extract(), opts); auto message: messageCursor) {
                Entity::SQS::Message result;
                result.FromDocument(message);
                messageList.push_back(result);
            }
        }
        log_trace << "Got message list, size: " << messageList.size();
        return messageList;
    }

    void SQSDatabase::ReceiveMessages(const std::string &queueArn, const int visibility, const int maxResult, const std::string &dlQueueArn, const int maxRetries, Entity::SQS::MessageList &messageList) const {

        // First reset resources
        const long resetCount = ResetMessages(queueArn, visibility);
        log_trace << "Messages reset, count " << resetCount;

        const auto reset = system_clock::now() + std::chrono::seconds(visibility);

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                mongocxx::options::find opts;
                if (maxResult > 0) {
                    opts.limit(maxResult);
                }

                session.start_transaction();

                // Get the cursor
                auto messageCursor = messageCollection.find(make_document(kvp("queueArn", queueArn),
                                                                          kvp("status", MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))),
                                                            opts);

                for (auto message: messageCursor) {

                    Entity::SQS::Message result;
                    result.FromDocument(message);

                    // Check retries
                    result.retries++;
                    if (maxRetries > 0 && result.retries >= maxRetries) {

                        // Send to DQL when existing
                        if (!dlQueueArn.empty()) {

                            std::string dlqQueueUrl = Core::AwsUtils::ConvertSQSQueueArnToUrl(dlQueueArn);
                            std::string dlqQueueName = Core::AwsUtils::ConvertSQSQueueArnToName(dlQueueArn);
                            messageCollection.update_one(make_document(kvp("_id", message["_id"].get_oid())),
                                                         make_document(kvp("$set", make_document(kvp("retries", 0),
                                                                                                 kvp("queueArn",
                                                                                                     dlQueueArn),
                                                                                                 kvp("queueUrl",
                                                                                                     dlqQueueUrl),
                                                                                                 kvp("queueName",
                                                                                                     dlqQueueName),
                                                                                                 kvp("status",
                                                                                                     MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))))));
                            log_debug << "Message send to DQL, id: " << result.oid << " queueArn: " << dlQueueArn;

                        } else {

                            // Delete message
                            long deleted = DeleteMessage(result);
                            log_debug << "Message deleted, id: " << result.oid << " queueArn: " << queueArn << " count: " << deleted;
                        }

                    } else {

                        result.receiptHandle = Core::AwsUtils::CreateSqsReceiptHandler();
                        messageList.push_back(result);

                        messageCollection.update_one(make_document(kvp("_id", message["_id"].get_oid())),
                                                     make_document(kvp("$set",
                                                                       make_document(kvp("status", MessageStatusToString(Entity::SQS::MessageStatus::INVISIBLE)),
                                                                                     kvp("reset", bsoncxx::types::b_date(reset)),
                                                                                     kvp("receiptHandle", result.receiptHandle),
                                                                                     kvp("retries", result.retries)))));
                        log_debug << "Message updated, id: " << result.oid << " queueArn: " << queueArn;
                    }
                }

                // Commit
                session.commit_transaction();

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            _memoryDb.ReceiveMessages(queueArn, visibility, maxResult, dlQueueArn, maxRetries, messageList);
        }
        log_trace << "Messages received, queueArn: " << queueArn + " count: " << messageList.size();
    }

    long SQSDatabase::ResetMessages(const std::string &queueArn, long visibility) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            const auto reset = std::chrono::system_clock::now() - std::chrono::seconds{visibility};

            try {

                session.start_transaction();
                const auto result = messageCollection.update_many(
                        make_document(
                                kvp("queueArn", queueArn),
                                kvp("status", Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INVISIBLE)),
                                kvp("reset", make_document(
                                                     kvp("$lt", bsoncxx::types::b_date(std::chrono::system_clock::now()))))),
                        make_document(kvp("$set",
                                          make_document(
                                                  kvp("status",
                                                      Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL)),
                                                  kvp("receiptHandle", ""),
                                                  kvp("reset", bsoncxx::types::b_date(reset))))));

                session.commit_transaction();

                log_trace << "Message reset, updated: " << result->upserted_count() << " queueArn: " << queueArn;

                return result->upserted_count();

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            return _memoryDb.ResetMessages(queueArn, visibility);
        }
        return 0;
    }

    void SQSDatabase::RedriveMessages(const std::string &queueArn, const Entity::SQS::RedrivePolicy &redrivePolicy) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                std::string dlqQueueUrl = Core::AwsUtils::ConvertSQSQueueArnToUrl(redrivePolicy.deadLetterTargetArn);
                std::string dlqQueueName = Core::AwsUtils::ConvertSQSQueueArnToName(redrivePolicy.deadLetterTargetArn);
                const auto result = messageCollection.update_many(make_document(kvp("queueArn", queueArn),
                                                                                kvp("retries", make_document(
                                                                                                       kvp("$gt", redrivePolicy.maxReceiveCount)))),
                                                                  make_document(kvp("$set", make_document(kvp("retries", 0),
                                                                                                          kvp("queueArn",
                                                                                                              redrivePolicy.deadLetterTargetArn),
                                                                                                          kvp("queueUrl",
                                                                                                              dlqQueueUrl),
                                                                                                          kvp("queueName",
                                                                                                              dlqQueueName),
                                                                                                          kvp("status",
                                                                                                              Entity::SQS::MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))))));
                session.commit_transaction();
                log_trace << "Message re-drive, arn: " << redrivePolicy.deadLetterTargetArn << " updated: " << result->modified_count() << " queueArn: " << queueArn;

            } catch (mongocxx::exception &e) {
                log_error << "Collection transaction exception: " << e.what();
                session.abort_transaction();
            }

        } else {

            _memoryDb.RedriveMessages(queueArn, redrivePolicy);
        }
    }

    long SQSDatabase::ResetDelayedMessages(const std::string &queueArn, const long delay) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto now = std::chrono::system_clock::now();
                const auto result = messageCollection.update_many(
                        make_document(
                                kvp("queueArn", queueArn),
                                kvp("status", MessageStatusToString(Entity::SQS::MessageStatus::DELAYED)),
                                kvp("reset", make_document(
                                                     kvp("$lt", bsoncxx::types::b_date(now))))),
                        make_document(
                                kvp("$set",
                                    make_document(
                                            kvp("status", MessageStatusToString(Entity::SQS::MessageStatus::INITIAL))))));
                session.commit_transaction();

                log_trace << "Delayed message reset, updated: " << result->upserted_count() << " queueArn: " << queueArn;

                return result->upserted_count();

            } catch (mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Collection transaction exception: " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.ResetDelayedMessages(queueArn, delay);
        }
    }

    long SQSDatabase::MessageRetention(const std::string &queueUrl, const long retentionPeriod) const {

        const auto reset = system_clock::now() - std::chrono::seconds{retentionPeriod};

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_many(
                        make_document(
                                kvp("queueUrl", queueUrl),
                                kvp("created", make_document(
                                                       kvp("$lt", bsoncxx::types::b_date(reset))))));
                session.commit_transaction();

                log_trace << "Message retention reset, deleted: " << result->deleted_count() << " queue: " << queueUrl;

                return result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.MessageRetention(queueUrl, retentionPeriod);
        }
    }

    long SQSDatabase::CountMessages(const std::string &queueArn, const std::string &prefix) const {

        if (HasDatabase()) {

            long count = 0;
            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            bsoncxx::builder::basic::document query = {};
            if (!queueArn.empty()) {
                query.append(kvp("queueArn", queueArn));
            }
            if (!prefix.empty()) {
                query.append(kvp("key", make_document(kvp("$regex", "^" + prefix))));
            }

            count = messageCollection.count_documents(query.extract());
            log_trace << "Count messages, queueArn: " << queueArn << " result: " << count;

            return count;

        } else {

            return _memoryDb.CountMessages(queueArn);
        }
    }

    long SQSDatabase::CountMessageSize(const std::string &queueArn) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            mongocxx::pipeline p{};
            if (!queueArn.empty()) {
                p.match(make_document(kvp("queueArn", queueArn)));
            }
            p.group(make_document(kvp("_id", ""),
                                  kvp("totalSize",
                                      make_document(kvp("$sum", "$size")))));
            p.project(make_document(kvp("_id", 0), kvp("totalSize", "$totalSize")));
            auto totalSizeCursor = messageCollection.aggregate(p);
            if (const auto t = *totalSizeCursor.begin(); !t.empty()) {
                log_info << "Total size: " << t["totalSize"].get_int64().value;
                return t["totalSize"].get_int64().value;
            }

            return 0;

        } else {

            return _memoryDb.CountMessages(queueArn);
        }
    }

    long SQSDatabase::CountMessagesByStatus(const std::string &queueArn, const Entity::SQS::MessageStatus &status) const {

        if (HasDatabase()) {

            try {

                const auto client = ConnectionPool::instance().GetConnection();
                auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

                const long count = messageCollection.count_documents(make_document(kvp("queueArn", queueArn),
                                                                                   kvp("status",
                                                                                       MessageStatusToString(status))));
                log_trace << "Count resources by status, status: " << MessageStatusToString(status) << " result: " << count;
                return count;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.CountMessagesByStatus(queueArn, status);
        }
    }

    Entity::SQS::MessageWaitTime SQSDatabase::GetAverageMessageWaitingTime() const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];

            try {
                Entity::SQS::MessageWaitTime waitTime;
                mongocxx::options::find opts;
                opts.limit(1);

                for (Entity::SQS::QueueList queueList = ListQueues(); const auto &queue: queueList) {

                    opts.sort(make_document(kvp("created", -1)));

                    system_clock::time_point firstTimestamp = system_clock::now();
                    system_clock::time_point lastTimestamp = system_clock::now();

                    if (const std::optional<bsoncxx::document::value> first = messageCollection.find_one(make_document(kvp("queueArn", queue.queueArn)), opts)) {
                        Entity::SQS::Message firstMessage;
                        firstMessage.FromDocument(first->view());
                        firstTimestamp = firstMessage.created;
                    }

                    opts.sort(make_document(kvp("created", 1)));

                    std::optional<bsoncxx::document::value> last = messageCollection.find_one(make_document(kvp("queueArn", queue.queueArn)), opts);
                    if (last.has_value()) {
                        Entity::SQS::Message lastMessage;
                        lastMessage.FromDocument(last->view());
                        lastTimestamp = lastMessage.created;
                    }

                    const double max = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - firstTimestamp).count();
                    if (const double min = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - lastTimestamp).count(); max + min > 5) {
                        waitTime.waitTime[queue.name] = (max + min) / 2.0;
                    } else {
                        waitTime.waitTime[queue.name] = 0.0;
                    }
                }
                return waitTime;
            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.GetAverageMessageWaitingTime();
        }
    }

    long SQSDatabase::DeleteMessages(const std::string &queueArn) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_many(make_document(kvp("queueArn", queueArn)));
                session.commit_transaction();
                log_debug << "Messages deleted, queueArn: " << queueArn << " count: " << result->deleted_count();
                return result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.DeleteMessages(queueArn);
        }
    }

    long SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_one(make_document(kvp("receiptHandle", message.receiptHandle)));
                session.commit_transaction();

                log_debug << "Messages deleted, receiptHandle: " << Core::StringUtils::SubString(message.receiptHandle, 0, 40) << "... count: " << result->deleted_count();
                return result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.DeleteMessage(message);
        }
    }

    long SQSDatabase::DeleteMessage(const std::string &receiptHandle) const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_one(make_document(kvp("receiptHandle", receiptHandle)));
                session.commit_transaction();
                log_debug << "Messages deleted, receiptHandle: " << Core::StringUtils::SubString(receiptHandle, 0, 40) << "... count: " << result->deleted_count();

                return result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.DeleteMessage(receiptHandle);
        }
    }

    void SQSDatabase::DeleteAllMessages() const {

        if (HasDatabase()) {

            const auto client = ConnectionPool::instance().GetConnection();
            auto messageCollection = (*client)[_databaseName][_collectionNameMessage];
            auto queueCollection = (*client)[_databaseName][_collectionNameQueue];
            auto session = client->start_session();

            try {

                session.start_transaction();
                const auto result = messageCollection.delete_many({});

                // Adjust queue counters
                queueCollection.update_many({},
                                            make_document(kvp("$set", make_document(kvp("attributes.approximateNumberOfMessages", bsoncxx::types::b_int64()),
                                                                                    kvp("attributes.approximateNumberOfMessagesDelayed", bsoncxx::types::b_int64()),
                                                                                    kvp("attributes.approximateNumberOfMessagesNotVisible", bsoncxx::types::b_int64())))));
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

}// namespace AwsMock::Database
