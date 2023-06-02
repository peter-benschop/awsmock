//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/SQSService.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    SQSService::SQSService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {
        Initialize();
    }

    void SQSService::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("S3Service");

        // Initialize environment
        _database = std::make_unique<Database::SQSDatabase>(_configuration);
    }

    Dto::SQS::CreateQueueResponse SQSService::CreateQueue(const Dto::SQS::CreateQueueRequest &request) {

        Dto::SQS::CreateQueueResponse createQueueResponse;
        try {
            // Check existence
            if (_database->QueueExists(request.region, request.name)) {
                throw Core::ServiceException("SQS Queue exists already", 500);
            }

            // Update database
            Database::Entity::SQS::Queue queue = _database->CreateQueue({.name=request.name, .region=request.region, .owner=request.owner, .url=request.url});

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "SQS create queue failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return createQueueResponse;
    }

    Dto::SQS::ListQueueResponse SQSService::ListQueues(const std::string &region) {
        poco_trace(_logger, "List all queues request, region: " + region);

        try {

            Database::Entity::SQS::QueueList queueList = _database->ListQueues(region);
            Dto::SQS::ListQueueResponse listQueueResponse = Dto::SQS::ListQueueResponse(queueList);
            poco_trace(_logger, "SQS create queue list response: " + listQueueResponse.ToXml());

            return listQueueResponse;

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "SQS list queues failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500, "SQS", Poco::UUIDGenerator().createRandom().toString().c_str());
        }
    }

    Dto::SQS::PurgeQueueResponse SQSService::PurgeQueue(const Dto::SQS::PurgeQueueRequest &request) {
        poco_trace(_logger, "Purge queue request, region: " + request.region + " queueUrl: " + request.queueUrl);

        Dto::SQS::PurgeQueueResponse response = {.resource=request.resource, .requestId=request.requestId};
        try {
            // Check existence
            if (!_database->QueueExists(request.queueUrl)) {
                throw Core::ServiceException("SQS queue does not exists", 500, request.resource.c_str(), request.requestId.c_str());
            }

            _database->PurgeQueue(request.region, request.queueUrl);
            poco_trace(_logger, "SQS queue purged, region: " + request.region + " queueUrl: " + request.queueUrl);

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "SQS purge queue failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500, request.resource.c_str(), request.requestId.c_str());
        }
        return response;
    }

    Dto::SQS::CreateMessageResponse SQSService::CreateMessage(const Dto::SQS::CreateMessageRequest &request) {

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
                _database->CreateMessage({.queue=request.url, .body=request.body, .messageId=messageId, .receiptHandle=receiptHandle, .md5Body=md5Body, .md5Attr=md5Attr});

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "SQS create message failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return {message};
    }

    Dto::SQS::DeleteQueueResponse SQSService::DeleteQueue(const Dto::SQS::DeleteQueueRequest &request) {
        poco_trace(_logger, "Delete queue request, url: " + request.url);

        Dto::SQS::DeleteQueueResponse response;
        try {
            // Check existence
            if (!_database->QueueExists(request.url)) {
                throw Core::ServiceException("Queue does not exist", 500);
            }

            // Update database
            _database->DeleteQueue({.url=request.url});

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "SQS delete queue failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return response;
    }

} // namespace AwsMock::Service
