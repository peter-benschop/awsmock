//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/worker/S3Monitoring.h"

namespace AwsMock::Worker {

  S3Monitoring::S3Monitoring(const Core::Configuration &configuration, Core::MetricService &metricService)
      : _logger(Poco::Logger::get("S3Monitoring")), _configuration(configuration), _metricService(metricService), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.s3.period", S3_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _s3Database = std::make_unique<Database::S3Database>(_configuration);
    log_debug_stream(_logger) << "S3 monitoring initialized" << std::endl;
  }

  void S3Monitoring::run() {

    log_info_stream(_logger) << "S3 monitoring started" << std::endl;

    _running = true;
    while (_running) {
      _logger.debug() << "S3 monitoring processing started" << std::endl;
      UpdateCounters();
      Poco::Thread::sleep(_period);
    }
  }

  void S3Monitoring::UpdateCounters() {
    long buckets = _s3Database->BucketCount();
    long objects = _s3Database->ObjectCount();
    _metricService.SetGauge("s3_bucket_count_total", buckets);
    _metricService.SetGauge("s3_object_count_total", objects);
    for(const auto &bucket : _s3Database->ListBuckets()) {
      std::string labelValue = Poco::replace(bucket.name, "-", "_");
      long objectsPerBucket = _s3Database->ObjectCount(bucket);
      _metricService.SetGauge("s3_bucket_count", "bucket", labelValue, objectsPerBucket);
    }
  }
} // namespace AwsMock::Worker
