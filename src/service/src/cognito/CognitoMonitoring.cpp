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
    log_debug_stream(_logger) << "Cognito monitoring initialized" << std::endl;
  }

  CognitoMonitoring::~CognitoMonitoring() {
    _condition.signal();
  }

  void CognitoMonitoring::run() {

    log_info_stream(_logger) << "Cognito monitoring started" << std::endl;

    if (_period <= 0) {
      return;
    }

    _running = true;
    while (_running) {

      _logger.debug() << "Cognito monitoring processing started" << std::endl;

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
    long userPools = _cognitoDatabase->CountUserPools();
    _metricService.SetGauge("cognito_userpool_count_total", userPools);
  }

} // namespace AwsMock::Worker
