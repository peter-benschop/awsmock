//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/SQSMonitoring.h>

namespace AwsMock::Worker {

  SQSMonitoring::SQSMonitoring(const Core::Configuration &configuration, Core::MetricService &metricService)
      : _logger(Poco::Logger::get("SQSMonitoring")), _configuration(configuration), _metricService(metricService), _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.sqs.period", SQS_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _sqsDatabase = std::make_unique<Database::SQSDatabase>(_configuration);
    log_debug_stream(_logger) << "SQS monitoring initialized" << std::endl;
  }

  void SQSMonitoring::run() {

    log_info_stream(_logger) << "SQS monitoring started" << std::endl;

    _running = true;
    while (_running) {
      _logger.debug() << "SQS monitoring processing started" << std::endl;
      UpdateCounters();
      Poco::Thread::sleep(_period);
    }
  }

  void SQSMonitoring::UpdateCounters() {

    // Get total counts
    long queues = _sqsDatabase->CountQueues();
    long messages = _sqsDatabase->CountMessages();
    _metricService.SetGauge("sqs_queue_count_total", queues);
    _metricService.SetGauge("sqs_message_count_total", messages);

    // Count messages per queue
    for(const auto &queue : _sqsDatabase->ListQueues()) {
      std::string labelValue = Poco::replace(queue.name, "-", "_");
      long messagesPerQueue = _sqsDatabase->CountMessages(queue.region, queue.queueUrl);
      _metricService.SetGauge("sqs_message_count", "queue", labelValue, messagesPerQueue);
    }
    log_debug_stream(_logger) << "SQS update counter finished" << std::endl;
  }
} // namespace AwsMock::Worker
