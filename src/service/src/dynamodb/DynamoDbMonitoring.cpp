//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/DynamoDbMonitoring.h>

namespace AwsMock::Service {

  DynamoDbMonitoring::DynamoDbMonitoring(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
      : _logger(Poco::Logger::get("DynamoDbMonitoring")), _configuration(configuration), _metricService(metricService), _dynamoDbDatabase(Database::DynamoDbDatabase::instance()), _condition(condition), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.dynamodb.period", DYNAMODB_MONITORING_DEFAULT_PERIOD);

    // Database connections

    log_debug_stream(_logger) << "DynamoDb monitoring initialized" << std::endl;
  }

  void DynamoDbMonitoring::run() {

    if (_period <= 0) {
      return;
    }
    log_info_stream(_logger) << "DynamoDb monitoring started" << std::endl;

    _running = true;
    while (_running) {

      _logger.debug() << "DynamoDb monitoring processing started" << std::endl;

      // Update counters
      UpdateCounters();

      // Wait for timeout or condition
      _mutex.lock();
      if (_condition.tryWait(_mutex, _period)) {
        break;
      }
      _mutex.unlock();
    }
  }

  void DynamoDbMonitoring::UpdateCounters() {
    //long DynamoDbs = _dynamoDbDatabase->DynamoDbCount();
    //_metricService.SetGauge("DynamoDb_count_total", DynamoDbs);
  }

} // namespace AwsMock::Service
