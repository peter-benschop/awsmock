//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    S3Service::S3Service(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {
        Initialize();
    }

    void S3Service::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("S3Service");

        // Initialize environment
        _database = std::make_unique<Database::S3Database>(_configuration);
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";

        // Create temp directory
        if (!Core::DirUtils::DirectoryExists(_tempDir)) {
            Core::DirUtils::MakeDirectory(_tempDir);
        }
    }

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(const std::string &name, const std::string &owner, const Dto::S3::CreateBucketRequest &s3Request) {
        poco_trace(_logger, "Create bucket request, s3Request: " + s3Request.ToString());

        Dto::S3::CreateBucketResponse createBucketResponse;
        try {
            // Get region
            std::string region = s3Request.GetLocationConstraint();

            // Check existence
            if (_database->BucketExists({.name=name, .region=region})) {
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
            poco_error(_logger, "S3 create bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return createBucketResponse;
    }

    Dto::S3::GetMetadataResponse S3Service::GetMetadata(Dto::S3::GetMetadataRequest &request) {
        poco_trace(_logger, "Get metadata request, s3Request: " + request.ToString());

        Dto::S3::GetMetadataResponse getMetadataResponse;
        try {

            Database::Entity::S3::Object object = _database->GetObject(request.GetBucket(), request.GetKey());
            getMetadataResponse.SetBucket(object.bucket);
            getMetadataResponse.SetKey(object.key);
            getMetadataResponse.SetSize(object.size);
            getMetadataResponse.SetMd5Sum(object.md5sum);
            getMetadataResponse.SetContentType(object.contentType);
            getMetadataResponse.SetLastModified(Poco::DateTimeFormatter::format(object.modified, Poco::DateTimeFormat::HTTP_FORMAT));
            poco_trace(_logger, "S3 get metadata response: " + getMetadataResponse.ToString());

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 create bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return getMetadataResponse;
    }

    Dto::S3::GetObjectResponse S3Service::GetObject(Dto::S3::GetObjectRequest &request) {
        poco_trace(_logger, "Get object request, s3Request: " + request.ToString());

        Dto::S3::GetObjectResponse getObjectResponse;
        try {

            Database::Entity::S3::Object object = _database->GetObject(request.GetBucket(), request.GetKey());

            std::string filename = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + request.GetBucket() + Poco::Path::separator() + request.GetKey();
            getObjectResponse.SetBucket(object.bucket);
            getObjectResponse.SetKey(object.key);
            getObjectResponse.SetSize(object.size);
            getObjectResponse.SetContentType(object.contentType);
            getObjectResponse.SetFilename(filename);
            getObjectResponse.SetLastModified(Poco::DateTimeFormatter::format(object.modified, Poco::DateTimeFormat::HTTP_FORMAT));
            poco_trace(_logger, "S3 get object response: " + getObjectResponse.ToString());

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 create bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return getObjectResponse;
    }

    Dto::S3::ListAllBucketResponse S3Service::ListAllBuckets() {
        poco_trace(_logger, "List all buckets request");

        try {

            Database::Entity::S3::BucketList bucketList = _database->ListBuckets();
            Dto::S3::ListAllBucketResponse listAllBucketResponse = Dto::S3::ListAllBucketResponse(bucketList);
            poco_trace(_logger, "S3 Create Bucket List outcome: " + listAllBucketResponse.ToXml());
            return listAllBucketResponse;

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 Create Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::S3::ListBucketResult S3Service::ListBucket(const std::string &bucket) {
        poco_trace(_logger, "List bucket request");

        try {

            Database::Entity::S3::ObjectList objectList = _database->ListBucket(bucket);
            Dto::S3::ListBucketResult listBucketResult = Dto::S3::ListBucketResult(objectList);
            poco_trace(_logger, "S3 list bucket result: " + listBucketResult.ToXml());
            return listBucketResult;

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 list bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::S3::InitiateMultipartUploadResult S3Service::CreateMultipartUpload(std::string &bucket, std::string &key, const std::string &region, const std::string &user) {
        poco_trace(_logger, "CreateMultipartUpload request, bucket: " + bucket + " key: " + key + " region: " + region + " user: " + user);

        // Check existence
        if (!_database->BucketExists({.name=bucket, .region=region})) {
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

        // Create directory, if not existing
        std::string fileDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + bucket + Poco::Path::separator() + GetDirFromKey(key);
        if (!Core::DirUtils::DirectoryExists(fileDir)) {
            Core::DirUtils::MakeDirectory(fileDir);
        }

        // Get all fie parts
        std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(_tempDir, updateId);

        // Output file
        std::string outFile = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
        poco_trace(_logger, "Output file, outFile: " + outFile);

        // Append all parts to the output file
        Core::FileUtils::AppendBinaryFiles(outFile, _tempDir, files);
        poco_trace(_logger, "Input files appended to outfile, outFile: " + outFile);

        // Create database object
        _database->CreateObject({.bucket=bucket, .key=key, .owner=user});

        // Cleanup
        Core::DirUtils::DeleteFilesInDirectory(_tempDir);

        return {region, bucket, key, Core::StringUtils::GenerateRandomString(40)};
    }

    Dto::S3::PutObjectResponse S3Service::PutObject(Dto::S3::PutObjectRequest &request, std::istream &stream) {
        poco_trace(_logger, "Put object request: " + request.ToString());

        Dto::S3::PutObjectResponse response;
        try {
            // Check existence
            if (!_database->BucketExists({.name=request.GetBucket(), .region=request.GetRegion()})) {
                throw Core::ServiceException("Bucket does not exist", 500);
            }

            // Create directory, if not existing
            std::string fileDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + request.GetBucket() + Poco::Path::separator() + GetDirFromKey(request.GetKey());
            if (!Core::DirUtils::DirectoryExists(fileDir)) {
                Core::DirUtils::MakeDirectory(fileDir);
            }

            // Write file
            std::string
                fileName = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + request.GetBucket() + Poco::Path::separator() + request.GetKey();
            std::ofstream ofs(fileName);
            ofs << stream.rdbuf();
            ofs.close();

            // Update database
            Database::Entity::S3::Object object;
            object = _database->CreateObject({.bucket=request.GetBucket(), .key=request.GetKey(), .owner=request.GetOwner(), .size=request.GetSize(),
                                                 .md5sum=request.GetMd5Sum(), .contentType=request.GetContentType()});

            response.SetETag(request.GetMd5Sum());

            // Check notification
            if(_database->HasBucketNotification({.bucket=request.GetBucket(), .region=request.GetRegion()})) {
                CheckNotifications(object, request.GetRegion(), "s3:ObjectCreated:Put");
            }

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 Delete Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
        return response;
    }

    void S3Service::PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request) {
        poco_trace(_logger, "Put bucket notification request, id: " + std::to_string(request.notificationId));

        try {
            // Check existence
            if (!_database->BucketExists({.name=request.bucket, .region=request.region})) {
                throw Core::ServiceException("Bucket does not exist", 500);
            }

            Database::Entity::S3::BucketNotification
                bucketNotification = _database->CreateBucketNotification({.bucket=request.bucket, .region=request.region, .notificationId=request.notificationId,
                                                                             .function=request.function, .event=request.event});

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 put bucket notification request failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    bool S3Service::HasEventNotification(const std::string &region, const std::string &bucket, const std::string &event) {
        poco_trace(_logger, "Has event notification, region: " + region + " bucket: " + bucket);

        Database::Entity::S3::BucketNotification notification = {.bucket=bucket, .region=region, .event=event};
        return _database->HasBucketNotification(notification);
    }

    void S3Service::CheckNotifications(Database::Entity::S3::Object object, const std::string &region, const std::string &event) {

        Database::Entity::S3::BucketNotification notification = _database->GetBucketNotification({.bucket=object.bucket, .region=region, .event=event});

        // Create the event record
        Dto::S3::Record record = {.s3.bucket=notification.bucket, .s3.object.key=object.key, .s3.object.etag=object.md5sum, .s3.object.size=object.size};
        Dto::S3::EventNotification eventNotification;
        eventNotification.records.push_back(record);

    }

    void S3Service::DeleteBucket(const std::string &region, const std::string &name) {
        poco_trace(_logger, "Delete bucket request, name: " + name);

        try {
            // Check existence
            if (!_database->BucketExists({.name=name, .region=region})) {
                throw Core::ServiceException("Bucket does not exist", 500);
            }

            // Delete directory
            std::string bucketDir = _dataDir + Poco::Path::separator() + "s3" + Poco::Path::separator() + name;
            if (Core::DirUtils::DirectoryExists(bucketDir)) {
                Core::DirUtils::DeleteDirectory(bucketDir);
            }

            // Update database
            _database->DeleteBucket({.name=name,.region=region});

        } catch (Poco::Exception &ex) {
            poco_error(_logger, "S3 Delete Bucket failed, message: " + ex.message());
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    std::string S3Service::GetDirFromKey(const std::string &key) {
        if (key.find('/') != std::string::npos) {
            return key.substr(0, key.find_last_of('/'));
        }
        return {};
    }

} // namespace AwsMock::Service
