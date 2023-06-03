//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/S3Worker.h>
#include "awsmock/core/ResourceNotFoundException.h"

namespace AwsMock::Worker {

    S3Worker::S3Worker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Worker")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("S3Worker");

        Initialize();

        poco_debug(_logger, "S3Worker initialized");
    }

    S3Worker::~S3Worker() {
        _watcherThread.wakeUp();
        delete _watcher;
    }

    void S3Worker::Initialize() {

        _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "s3";
        poco_debug(_logger, "Watching path: " + _dataDir);

        // Create S3 directory
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _s3Database = std::make_unique<Database::S3Database>(_configuration);

        // Start watcher
        _watcher = new Core::DirectoryWatcher(_dataDir);
        _watcher->itemAdded += Poco::delegate(this, &S3Worker::OnFileAdded);
        _watcher->itemModified += Poco::delegate(this, &S3Worker::OnFileModified);
        _watcher->itemDeleted += Poco::delegate(this, &S3Worker::OnFileDeleted);
        poco_debug(_logger, "Directory watcher added, path: " + _dataDir);
    }

    void S3Worker::OnFileAdded(const Core::DirectoryEvent &addedEvent) {
        poco_debug(_logger, "Added path: " + addedEvent.item.path());

        // Get bucketName, key
        std::string bucketName, key;
        GetBucketKeyFromFile(addedEvent.item.path(), bucketName, key);

        // Get file size, MD5 sum
        long fileSize = Core::FileUtils::FileSize(addedEvent.item.path());
        std::string md5sum = Core::Crypto::GetMd5FromFile(addedEvent.item.path());
        std::string owner = Core::FileUtils::GetOwner(addedEvent.item.path());

        Database::Entity::S3::Bucket bucket = {.name=bucketName, .region=_region, .owner=owner};
        if (!_s3Database->BucketExists(bucket)) {
            _s3Database->CreateBucket(bucket);
        }

        Database::Entity::S3::Object object = {.bucket=bucketName, .key=key, .owner=owner,.size=fileSize, .md5sum=md5sum};
        if (!_s3Database->ObjectExists(object)){
            _s3Database->CreateObject(object);
        }
    }

    void S3Worker::OnFileModified(const Core::DirectoryEvent &modifiedEvent) {
        poco_debug(_logger, "Changed path: " + modifiedEvent.item.path());

        // Get bucketName, key
        std::string bucketName, key;
        GetBucketKeyFromFile(modifiedEvent.item.path(), bucketName, key);

        // Get file size, MD5 sum
        long fileSize = Core::FileUtils::FileSize(modifiedEvent.item.path());
        std::string md5sum = Core::Crypto::GetMd5FromFile(modifiedEvent.item.path());
        std::string owner = Core::FileUtils::GetOwner(modifiedEvent.item.path());

        Database::Entity::S3::Object object = {.bucket=bucketName, .key=key, .owner=owner, .size=fileSize, .md5sum=md5sum};
        if (_s3Database->ObjectExists(object)){
            _s3Database->UpdateObject(object);
        } else {
            _s3Database->CreateObject(object);
        }
    }

    void S3Worker::OnFileDeleted(const Core::DirectoryEvent &deleteEvent) {
        poco_debug(_logger, "Deleted path: " + deleteEvent.item.path());

        std::string bucketName, key;
        GetBucketKeyFromFile(deleteEvent.item.path(), bucketName, key);

        Database::Entity::S3::Bucket bucket = {.name=bucketName, .region=_region};
        Database::Entity::S3::Object object = {.bucket=bucketName, .key = key};
        if (_s3Database->BucketExists(bucket) && _s3Database->ObjectExists(object)){
            _s3Database->DeleteObject(object);
        }
    }

    [[noreturn]] void S3Worker::run() {

        _watcherThread.start(_watcher);

        while (true) {
            Poco::Thread::sleep(10000);
        }
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
