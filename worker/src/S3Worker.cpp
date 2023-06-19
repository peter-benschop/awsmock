//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/S3Worker.h>
#include "awsmock/core/ResourceNotFoundException.h"

namespace AwsMock::Worker {

    S3Worker::S3Worker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Worker")), _configuration(configuration), _running(false) {
        Core::Logger::SetDefaultConsoleLogger("S3Worker");

        Initialize();

        _logger.debug() << "S3Worker initialized" << std::endl;
    }

    S3Worker::~S3Worker() {
        _watcherThread.wakeUp();
        delete _watcher;
    }

    void S3Worker::Initialize() {

        _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "s3";
        _logger.debug() << "Watching path: " << _dataDir << std::endl;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.s3.period", 10000);

        // Create S3 directory
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _s3Service = std::make_unique<Service::S3Service>(_configuration);
        _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);

        // Start _watcher
        _watcher = new Core::DirectoryWatcher(_dataDir);
        _watcher->itemAdded += Poco::delegate(this, &S3Worker::OnFileAdded);
        _watcher->itemModified += Poco::delegate(this, &S3Worker::OnFileModified);
        _watcher->itemDeleted += Poco::delegate(this, &S3Worker::OnFileDeleted);
        _logger.debug() << "Directory _watcher added, path: " << _dataDir << std::endl;
    }

    void S3Worker::run() {

        // Check service active
//        if (!_serviceDatabase->IsActive("S3")) {
//            return;
//        }

        // Start file watcher, they will call the delegate methods, if they find a file system event.
        _watcherThread.start(_watcher);

        _running = true;
        while (_running) {
            Poco::Thread::sleep(_period);
        }
    }

    void S3Worker::OnFileAdded(const Core::DirectoryEvent &addedEvent) {
        _logger.debug() << "Added path: " << addedEvent.item.path() << std::endl;

        // Get bucketName, key
        std::string bucketName, key;
        GetBucketKeyFromFile(addedEvent.item.path(), bucketName, key);

        // Get file size, MD5 sum
        long size = Core::FileUtils::FileSize(addedEvent.item.path());
        std::string md5sum = Core::Crypto::GetMd5FromFile(addedEvent.item.path());
        std::string owner = Core::FileUtils::GetOwner(addedEvent.item.path());

        Dto::S3::PutObjectRequest request = {.region=_region, .bucket=bucketName, .key=key, .md5Sum=md5sum, .size=size, .owner=owner};
        _s3Service->PutObject(request);
    }

    void S3Worker::OnFileModified(const Core::DirectoryEvent &modifiedEvent) {
        _logger.debug() << "Changed path: " << modifiedEvent.item.path() << std::endl;

        // Get bucketName, key
        std::string bucketName, key;
        GetBucketKeyFromFile(modifiedEvent.item.path(), bucketName, key);

        // Get file size, MD5 sum
        long size = Core::FileUtils::FileSize(modifiedEvent.item.path());
        std::string md5sum = Core::Crypto::GetMd5FromFile(modifiedEvent.item.path());
        std::string owner = Core::FileUtils::GetOwner(modifiedEvent.item.path());

        Dto::S3::PutObjectRequest request = {.region=_region, .bucket=bucketName, .key=key, .md5Sum=md5sum, .size=size, .owner=owner};
        _s3Service->PutObject(request);
    }

    void S3Worker::OnFileDeleted(const Core::DirectoryEvent &deleteEvent) {
        _logger.debug() << "Deleted path: " << deleteEvent.item.path() << std::endl;

        std::string bucketName, key;
        GetBucketKeyFromFile(deleteEvent.item.path(), bucketName, key);

        Database::Entity::S3::Bucket bucket = {.region=_region, .name=bucketName};
        Database::Entity::S3::Object object = {.bucket=bucketName, .key = key};

        Dto::S3::DeleteObjectRequest request = {.region=_region, .bucket=bucketName, .key=key};
        _s3Service->DeleteObject(request);
    }

    void S3Worker::GetBucketKeyFromFile(const std::string &fileName, std::string &bucket, std::string &key) {

        std::string file = Poco::replace(fileName, _dataDir.c_str(), "");

        Poco::RegularExpression::MatchVec posVec;
        Poco::RegularExpression pattern(R"(/([a-z0-9-.]+)/([a-zA-Z0-9-_/.*'()]+)$)");
        if (!pattern.match(file, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract bucket and key");
        }

        if (posVec.size() > 1) {
            bucket = file.substr(posVec[1].offset, posVec[1].length);
        }
        if (posVec.size() > 2) {
            key = file.substr(posVec[2].offset, posVec[2].length);
        }
    }

} // namespace AwsMock::Worker
