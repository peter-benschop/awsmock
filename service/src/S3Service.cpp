//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    S3Service::S3Service(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("S3Service");

        _database = std::make_unique<Database::S3Database>(_configuration);
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";

        // Create temp directory
        if(!Core::DirUtils::DirectoryExists(_tempDir)) {
            Core::DirUtils::MakeDirectory(_tempDir);
        }
    }

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(const std::string &name, const std::string &owner, const Dto::S3::CreateBucketRequest &s3Request) {
        poco_trace(_logger, "Create bucket request, s3Request: " + s3Request.ToString());

        Dto::S3::CreateBucketResponse createBucketResponse;
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
            _database->CreateBucket(region, name, owner);

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

    Dto::S3::InitiateMultipartUploadResult S3Service::CreateMultipartUpload(std::string &bucket, std::string &key, const std::string &region, const std::string &user) {
        poco_trace(_logger, "CreateMultipartUpload request, bucket: " + bucket + " key: " + key + " region: " + region + " user: " + user);

        // Check existence
        if (!_database->BucketExists(region, bucket)) {
            throw Core::ServiceException("Bucket does not exist", 500);
        }

        std::string uploadId = Core::StringUtils::GenerateRandomString(58);
        Dto::S3::InitiateMultipartUploadResult result = Dto::S3::InitiateMultipartUploadResult(bucket, key, uploadId);

        return result;
    }

    std::string S3Service::UploadPart(std::istream &stream, int part, const std::string &updateId) {
        poco_trace(_logger, "UploadPart request, part: " + std::to_string(part) + " updateId: " + updateId);

        std::ofstream ofs(_tempDir + Poco::Path::separator() + updateId + "-" + std::to_string(part));
        ofs << stream.rdbuf();

        return Core::StringUtils::GenerateRandomString(40);
    }

    Dto::S3::CompleteMultipartUploadResult S3Service::CompleteMultipartUpload(const std::string &updateId,
                                                                              const std::string &bucket,
                                                                              const std::string &key,
                                                                              const std::string &region,
                                                                              const std::string &user) {
        poco_trace(_logger, "CompleteMultipartUpload request, updateId: " + updateId + " bucket: " + bucket + " key: " + key + " region: " + region + " user: " + user);

        std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(_tempDir, updateId);

        std::string outFile = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
        poco_trace(_logger, "Output file, outFile: " + outFile);

        Core::FileUtils::AppendBinaryFiles(outFile, _tempDir, files);
        poco_trace(_logger, "Input files appended to outfile, outFile: " + outFile);

        // Cleanup
        Core::DirUtils::DeleteFilesInDirectory(_tempDir);

        std::string etag = Core::StringUtils::GenerateRandomString(40);
        Dto::S3::CompleteMultipartUploadResult result = Dto::S3::CompleteMultipartUploadResult(region, bucket, key, etag);

        return result;
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
