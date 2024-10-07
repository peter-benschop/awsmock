//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/s3/S3Worker.h>

namespace AwsMock::Service {

    void S3Worker::SyncObjects() {

        std::string region = Core::Configuration::instance().getString("awsmock.region");
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir");
        std::string s3DataDir = dataDir + "/s3/";

        Database::Entity::S3::BucketList buckets = _s3Database.ListBuckets();
        log_trace << "S3 worker starting, bucketCount: " << buckets.size();

        if (buckets.empty()) {
            return;
        }

        // Loop over buckets and do some maintenance work
        int filesDeleted = 0, objectsDeleted = 0;
        for (auto &bucket: buckets) {

            // Get objects and delete object, where the file is not existing anymore
            std::vector objects = _s3Database.GetBucketObjectList(region, bucket.name, 1000);
            for (const auto &object: objects) {
                if (!Core::FileUtils::FileExists(s3DataDir + object.internalName)) {
                    _s3Database.DeleteObject(object);
                    log_debug << "Object deleted, internalName: " << object.internalName;
                    objectsDeleted++;
                }
            }
        }

        boost::filesystem::path p(s3DataDir);
        if (is_directory(p)) {
            for (auto &entry: boost::make_iterator_range(directory_iterator(p), {})) {
                if (!_s3Database.ObjectExists(Core::FileUtils::GetBasename(entry.path().string()))) {
                    Core::FileUtils::DeleteFile(entry.path().string());
                    log_debug << "File deleted, filename: " << entry.path().string();
                    filesDeleted++;
                }
            }
        }
        log_debug << "Bucket synchronized, bucketCount: " << buckets.size() << " fileDeleted: " << filesDeleted << " objectsDeleted: " << objectsDeleted;
    }

}// namespace AwsMock::Service