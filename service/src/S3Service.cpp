//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    S3Service::S3Service(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("S3Service");

        _database = std::make_unique<Database::S3Database>(_configuration);
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/data");
    }

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(std::string &bucketName, const Dto::S3::CreateBucketRequest &s3Request) {
        poco_trace(_logger, "Create bucket request, s3Request: " + s3Request.ToString());

        Dto::S3::CreateBucketResponse createBucketResponse;
        Poco::Data::Session session = _database->GetSession();
        try {
            // Get region
            std::string region = s3Request.GetLocationConstraint();

            // Check existence
            if (_database->BucketExists(region, bucketName)) {
                throw Core::ServiceException("Bucket exists already", 500);
            }

            // Create directory
            std::string bucketDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + bucketName;
            if (!Core::DirUtils::DirectoryExists(bucketDir)) {
                Core::DirUtils::MakeDirectory(bucketDir);
            }

            // Update database
            _database->CreateBucket(region, bucketName);

            createBucketResponse = Dto::S3::CreateBucketResponse(region, "arn");
            poco_trace(_logger, "S3 Create Bucket outcome: " + createBucketResponse.ToXml());

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "S3 Create Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        session.close();

        return createBucketResponse;
    }

    Dto::S3::ListAllBucketResponse S3Service::ListAllBuckets() {
        poco_trace(_logger, "List bucket request");

        Poco::Data::Session session = _database->GetSession();
        try {

            Dto::S3::BucketList bucketList = _database->ListBuckets();
            Dto::S3::ListAllBucketResponse listAllBucketResponse = Dto::S3::ListAllBucketResponse(bucketList);
            poco_trace(_logger, "S3 Create Bucket List outcome: " + listAllBucketResponse.ToXml());

            session.close();

            return listAllBucketResponse;

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "S3 Create Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    void S3Service::DeleteBucket(const std::string &region, const std::string &name) {
        poco_trace(_logger, "Delete bucket request, name: " + name);

        Poco::Data::Session session = _database->GetSession();
        try {
            // Check existence
            if (!_database->BucketExists(region, name)) {
                throw Core::ServiceException("Bucket does not exist", 500);
            }

            // Delete directory
            std::string bucketDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + name;
            if (Core::DirUtils::DirectoryExists(bucketDir)) {
                Core::DirUtils::DeleteDirectory(bucketDir);
            }

            // Update database
            _database->DeleteBucket(region, name);

        } catch (Poco::Exception &ex) {
            session.close();
            poco_error(_logger, "S3 Delete Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        session.close();
    }
} // namespace AwsMock::Service
