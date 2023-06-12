//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/SNSService.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    SNSService::SNSService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("SNSService")), _configuration(configuration) {
        Initialize();
    }

    void SNSService::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("SNSService");

        // Initialize environment
        _database = std::make_unique<Database::SNSDatabase>(_configuration);
        _accountId = DEFAULT_ACCOUNT_ID;
    }

    Dto::SNS::CreateTopicResponse SNSService::CreateTopic(const Dto::SNS::CreateTopicRequest &request) {
        _logger.trace() << "Create topic request: " << request.ToString();

        Database::Entity::SNS::Topic topic;
        try {
            // Check existence
            if (_database->TopicExists(request.region, request.topicName)) {
                throw Core::ServiceException("SQS Queue exists already", 500);
            }

            // Update database
            std::string queueArn = Core::AwsUtils::CreateSQSArn(request.region, _accountId, request.name);
            queue = _database->CreateQueue({.region=request.region, .name=request.name, .owner=request.owner, .queueUrl=request.queueUrl, .queueArn=queueArn});
            _logger.trace() << "SQS queue created: " << queue.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "SQS create queue failed, message: " << exc.message();
            throw Core::ServiceException(exc.message(), 500);
        }*/
        return {};//{.region=queue.region, .name=queue.name, .owner=queue.owner, .queueUrl=queue.queueUrl};
    }
/*
    Dto::SQS::ListQueueResponse SNSService::ListQueues(const std::string &region) {
        _logger.trace() << "List all queues request, region: " << region;

        try {

            Database::Entity::SQS::QueueList queueList = _database->ListQueues(region);
            Dto::SQS::ListQueueResponse listQueueResponse = Dto::SQS::ListQueueResponse(queueList);
            _logger.trace() << "SQS create queue list response: " << listQueueResponse.ToXml();

            return listQueueResponse;

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS list queues failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500, "SQS", Poco::UUIDGenerator().createRandom().toString().c_str());
        }
    }

    Dto::SQS::PurgeQueueResponse SNSService::PurgeQueue(const Dto::SQS::PurgeQueueRequest &request) {
        _logger.trace() << "Purge queue request, region: " << request.region << " queueUrl: " << request.queueUrl;

        Dto::SQS::PurgeQueueResponse response = {.resource=request.resource, .requestId=request.requestId};
        try {
            // Check existence
            if (!_database->QueueExists(request.queueUrl)) {
                throw Core::ServiceException("SQS queue does not exists", 500, request.resource.c_str(), request.requestId.c_str());
            }

            _database->PurgeQueue(request.region, request.queueUrl);
            _logger.trace() << "SQS queue purged, region: " << request.region << " queueUrl: " << request.queueUrl;

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS purge queue failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500, request.resource.c_str(), request.requestId.c_str());
        }
        return response;
    }

    Dto::SQS::PutQueueAttributesResponse SNSService::PutQueueAttributes(const Dto::SQS::PutQueueAttributesRequest &request) {
        _logger.trace() << "Put queue sqs request, request: " << request.ToString();
        Dto::SQS::PutQueueAttributesResponse response;
        return response;
    }

    Dto::SQS::DeleteQueueResponse SNSService::DeleteQueue(const Dto::SQS::DeleteQueueRequest &request) {
        _logger.trace() << "Delete queue request, request: " << request.ToString();

        Dto::SQS::DeleteQueueResponse response;
        try {
            // Check existence
            if (!_database->QueueExists(request.queueUrl)) {
                throw Core::ServiceException("Queue does not exist", 500);
            }

            // Update database
            _database->DeleteQueue({.queueUrl=request.queueUrl});

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS delete queue failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
        return response;
    }

    Dto::SQS::CreateMessageResponse SNSService::CreateMessage(const Dto::SQS::CreateMessageRequest &request) {

        Database::Entity::SQS::Message message;
        try {
            // Check existence
            if (!_database->QueueExists(request.url)) {
                throw Core::ServiceException("SQS queue does not exists", 500);
            }

            // Update database
            std::string messageId = Core::StringUtils::GenerateRandomString(100);
            std::string receiptHandle = Core::StringUtils::GenerateRandomString(512);
            std::string md5Body = Core::Crypto::GetMd5FromString(request.body);
            std::string md5Attr = Core::Crypto::GetMd5FromString(request.body);
            message =
                _database->CreateMessage({.queueUrl=request.url, .body=request.body, .messageId=messageId, .receiptHandle=receiptHandle, .md5Body=md5Body, .md5Attr=md5Attr});

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS create message failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
        return {.queueUrl=message.queueUrl, .messageId=message.messageId, .receiptHandle=message.receiptHandle, .md5Body=message.md5Body, .md5Attr=message.md5Attr};
    }

    Dto::SQS::ReceiveMessageResponse SNSService::ReceiveMessages(const Dto::SQS::ReceiveMessageRequest &request) {

        Dto::SQS::ReceiveMessageResponse response;
        try {
            Database::Entity::SQS::MessageList messageList;

            long elapsed = 0;
            auto begin = std::chrono::high_resolution_clock::now();

            while (elapsed < request.waitTimeSeconds * 1000) {

                _database->ReceiveMessages(request.region, request.queueUrl, messageList);

                if(!messageList.empty()) {
                    break;
                }

                auto end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
                Poco::Thread::sleep(500);
            }

            if (!messageList.empty()) {
                response.messageList = messageList;
                response.requestId = Poco::UUIDGenerator().createRandom().toString();
            }

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS create message failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
        return {response};
    }

    Dto::SQS::DeleteMessageResponse SNSService::DeleteMessage(const Dto::SQS::DeleteMessageRequest &request) {
        _logger.trace() << "Delete message request, url: " << request.receiptHandle;

        Dto::SQS::DeleteMessageResponse response;
        try {
            // TODO: Check existence
            if (!_lambdaDatabase->MessageExists(request.url)) {
                throw Core::ServiceException("Queue does not exist", 500);
            }

            // Delete from database
            _database->DeleteMessage({.queueUrl=request.queueUrl, .receiptHandle=request.receiptHandle});

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS delete message failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
        return response;
    }*/

} // namespace AwsMock::Service
