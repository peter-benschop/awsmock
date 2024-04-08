//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/s3/S3Monitoring.h"

namespace AwsMock::Service {

  S3Monitoring::S3Monitoring(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
      : _logger(Poco::Logger::get("S3Monitoring")), _configuration(configuration), _metricService(metricService), _condition(condition), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.s3.period", S3_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _s3Database = std::make_unique<Database::S3Database>();
    log_debug_stream(_logger) << "S3 monitoring initialized" << std::endl;
  }

  S3Monitoring::~S3Monitoring() {
    _condition.signal();
  }

  void S3Monitoring::run() {

    log_info_stream(_logger) << "S3 monitoring started" << std::endl;

    if (_period <= 0) {
      return;
    }

    _running = true;
    while (_running) {

      _logger.debug() << "S3 monitoring processing started" << std::endl;

      // Update counter
      UpdateCounters();

      // Wait for timeout or condition
      _mutex.lock();
      if (_condition.tryWait(_mutex, _period)) {
        break;
      }
      _mutex.unlock();
    }
  }

  void S3Monitoring::Stop() { _condition.signal(); }

  void S3Monitoring::UpdateCounters() {
    long buckets = _s3Database->BucketCount();
    long objects = _s3Database->ObjectCount();
    _metricService.SetGauge("s3_bucket_count_total", buckets);
    _metricService.SetGauge("s3_object_count_total", objects);
    for (const auto &bucket : _s3Database->ListBuckets()) {
      std::string labelValue = Poco::replace(bucket.name, "-", "_");
      long objectsPerBucket = _s3Database->ObjectCount(bucket.region, bucket.name);
      _metricService.SetGauge("s3_bucket_count", "bucket", labelValue, objectsPerBucket);
    }
  }
} // namespace AwsMock::Worker
