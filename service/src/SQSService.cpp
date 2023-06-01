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
        //_dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
        //_tempDir = _dataDir + Poco::Path::separator() + "tmp";

        // Create temp directory
        //if (!Core::DirUtils::DirectoryExists(_tempDir)) {
        //    Core::DirUtils::MakeDirectory(_tempDir);
        //}
    }

    //Dto::SQS::CreateQueueResponse SQSService::CreateQueue(const std::string &name, const std::string &owner, const Dto::SQS::CreateQueueRequest &sqsRequest) {
//        poco_trace(_logger, "Create queue request, s3Request: " + sqsRequest.ToString());

        /*Dto::S3::CreateBucketResponse createBucketResponse;
        Poco::Data::Session session = _database->GetSession();
        try {
            // Get region
            std::string region = s3Request.GetLocationConstraint();

            // Check existence
            if (_database->BucketExists(region, name)) {
                throw Core::ServiceException("Bucket exists already", 500);
            }

            // Create directory
            std::string bucketDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + name;
            if (!Core::DirUtils::DirectoryExists(bucketDir)) {
                Core::DirUtils::MakeDirectory(bucketDir);
            }

            // Update database
            _database->CreateBucket({.name=name, .region=region, .owner=owner});

            createBucketResponse = Dto::S3::CreateBucketResponse(region, "arn");
            poco_trace(_logger, "S3 create bucket response: " + createBucketResponse.ToXml());

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "S3 create bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        session.close();*/

        //return createBucketResponse;
//        return {};
    //    }

    Dto::SQS::CreateQueueResponse SQSService::CreateQueue(const Dto::SQS::CreateQueueRequest &request) {

        Dto::SQS::CreateQueueResponse createQueueResponse;
        Poco::Data::Session session = _database->GetSession();
        try {
            // Check existence
            if (_database->QueueExists(request.region, request.name)) {
                throw Core::ServiceException("SQS Queue exists already", 500);
            }

            // Update database
            Database::Entity::SQS::Queue queue = _database->CreateQueue({.name=request.name, .region=request.region, .owner=request.owner, .url=request.url});

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "SQS create queue failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        session.close();

        return createQueueResponse;
    }

    Dto::SQS::ListQueueResponse SQSService::ListQueues(const std::string region) {
        poco_trace(_logger, "List all queues request");

        Poco::Data::Session session = _database->GetSession();
        try {

            Database::Entity::SQS::QueueList queueList = _database->ListQueues(region);
            Dto::SQS::ListQueueResponse listQueueResponse = Dto::SQS::ListQueueResponse(queueList);
            poco_trace(_logger, "SQS create queue list response: " + listQueueResponse.ToXml());

            session.close();

            return listQueueResponse;

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "SQS list queues failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::SQS::DeleteQueueResponse SQSService::DeleteQueue(const Dto::SQS::DeleteQueueRequest &request) {
        poco_trace(_logger, "Delete queue request, url: " + request.url);

        Dto::SQS::DeleteQueueResponse response;
        Poco::Data::Session session = _database->GetSession();
        try {
            // Check existence
            if (!_database->QueueExists(request.url)) {
                throw Core::ServiceException("Queue does not exist", 500);
            }

            // Update database
            _database->DeleteQueue({.url=request.url});

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "SQS delete queue failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        session.close();
        return response;
    }

} // namespace AwsMock::Service
