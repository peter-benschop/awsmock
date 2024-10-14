//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server(Core::PeriodicScheduler &scheduler) : AbstractServer("s3") {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.s3.monitoring.period", S3_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.s3.worker.period", S3_DEFAULT_WORKER_PERIOD);

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }

        // Start SNS monitoring update counters
        scheduler.AddTask("s3-monitoring-counters", [this] { UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        scheduler.AddTask("s3-sync-directories", [this] { SyncObjects(); }, _workerPeriod);
        log_debug << "S3 server initialized";
    }

    void S3Server::SyncObjects() {

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

    void S3Server::UpdateCounter() {
        log_trace << "S3 Monitoring starting";

        long buckets = _s3Database.BucketCount();
        long objects = _s3Database.ObjectCount();
        _metricService.SetGauge(S3_BUCKET_COUNT, static_cast<double>(buckets));
        _metricService.SetGauge(S3_OBJECT_COUNT, static_cast<double>(objects));

        // Count resources per topic
        for (const auto &bucket: _s3Database.ListBuckets()) {
            std::string labelValue = Poco::replace(bucket.name, "-", "_");
            long messagesPerTopic = _s3Database.ObjectCount(bucket.region, bucket.name);
            _metricService.SetGauge(S3_OBJECT_BY_BUCKET_COUNT, "bucket", labelValue, static_cast<double>(messagesPerTopic));
        }
        log_trace << "S3 monitoring finished";
    }

}// namespace AwsMock::Service
