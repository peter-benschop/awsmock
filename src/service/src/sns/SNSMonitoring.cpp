//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/SNSMonitoring.h>

namespace AwsMock::Service {

  SNSMonitoring::SNSMonitoring(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
      : _logger(Poco::Logger::get("SNSMonitoring")), _configuration(configuration), _metricService(metricService), _condition(condition),  _running(false) {

    // Update period
    _period = _configuration.getInt("awsmock.monitoring.sns.period", SNS_MONITORING_DEFAULT_PERIOD);

    // Database connections
    _snsDatabase = std::make_unique<Database::SNSDatabase>(_configuration);
    log_debug_stream(_logger) << "SNS monitoring initialized" << std::endl;
  }

  void SNSMonitoring::run() {

    log_info_stream(_logger) << "SNS monitoring started" << std::endl;

    _running = true;
    while (_running) {

      _logger.debug() << "SNS monitoring processing started" << std::endl;

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

  void SNSMonitoring::UpdateCounters() {

    // Get total counts
    long topics = _snsDatabase->CountTopics();
    long messages = _snsDatabase->CountMessages();
    _metricService.SetGauge("sns_topic_count_total", topics);
    _metricService.SetGauge("sns_message_count_total", messages);

    // Count messages per topic
    for(const auto &topic : _snsDatabase->ListTopics()) {
      std::string labelValue = Poco::replace(topic.topicName, "-", "_");
      long messagesPerQueue = _snsDatabase->CountMessages(topic.region, topic.topicArn);
      _metricService.SetGauge("sns_message_count", "topic", labelValue, messagesPerQueue);
    }
    log_debug_stream(_logger) << "SNS update counter finished" << std::endl;
  }
} // namespace AwsMock::Worker
