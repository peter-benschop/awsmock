//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/s3/S3Monitoring.h>

namespace AwsMock::Service {

    void S3Monitoring::Initialize() {
        UpdateCounter();
    }

    void S3Monitoring::Run() {
        UpdateCounter();
    }

    void S3Monitoring::Shutdown() {
        log_debug << "Shutting down, thread: s3-monitoring";
    }

    void S3Monitoring::UpdateCounter() {
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