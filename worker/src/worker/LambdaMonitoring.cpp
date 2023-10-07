//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/LambdaMonitoring.h>

namespace AwsMock::Worker {

  LambdaMonitoring::LambdaMonitoring(const Core::Configuration &configuration, Core::MetricService &metricService)
      : _logger(Poco::Logger::get("LambdaMonitoring")), _configuration(configuration), _metricService(metricService), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.lambda.period", LAMBDA_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _lambdaDatabase = std::make_unique<Database::LambdaDatabase>(_configuration);
    log_debug_stream(_logger) << "Lambda monitoring initialized" << std::endl;
  }

  void LambdaMonitoring::run() {

    log_info_stream(_logger) << "Lambda monitoring started" << std::endl;

    _running = true;
    while (_running) {
      _logger.debug() << "Lambda monitoring processing started" << std::endl;
      UpdateCounters();
      Poco::Thread::sleep(_period);
    }
  }

  void LambdaMonitoring::UpdateCounters() {
    long lambdas = _lambdaDatabase->LambdaCount();
    _metricService.SetGauge("lambda_count_total", lambdas);
  }

} // namespace AwsMock::Worker
