//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/CognitoMonitoring.h>

namespace AwsMock::Service {

  CognitoMonitoring::CognitoMonitoring(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
      : _logger(Poco::Logger::get("CognitoMonitoring")), _configuration(configuration), _metricService(metricService), _condition(condition), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.cognito.period", COGNITO_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _cognitoDatabase = std::make_unique<Database::CognitoDatabase>(_configuration);
    log_debug_stream(_logger) << "S3 monitoring initialized" << std::endl;
  }

  CognitoMonitoring::~CognitoMonitoring() {
    _condition.signal();
  }

  void CognitoMonitoring::run() {

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

  void CognitoMonitoring::Stop() { _condition.signal(); }

  void CognitoMonitoring::UpdateCounters() {
    /*long buckets = _cognitoDatabase->BucketCount();
    long objects = _cognitoDatabase->ObjectCount();
    _metricService.SetGauge("s3_bucket_count_total", buckets);
    _metricService.SetGauge("s3_object_count_total", objects);
    for (const auto &bucket : _cognitoDatabase->ListBuckets()) {
      std::string labelValue = Poco::replace(bucket.name, "-", "_");
      long objectsPerBucket = _cognitoDatabase->ObjectCount(bucket.region, bucket.name);
      _metricService.SetGauge("s3_bucket_count", "bucket", labelValue, objectsPerBucket);
    }*/

  }

} // namespace AwsMock::Worker
