//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

  SNSServer::SNSServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractServer(configuration, "sns"), _logger(Poco::Logger::get("SNSServer")), _configuration(configuration), _metricService(metricService), _snsDatabase(Database::SNSDatabase::instance()) {

    // HTTP manager configuration
    _port = _configuration.getInt("awsmock.service.sns.port", SNS_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.sns.host", SNS_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.sns.max.queue", SNS_DEFAULT_QUEUE_LENGTH);
    _maxThreads = _configuration.getInt("awsmock.service.sns.max.threads", SNS_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.sns.timeout", SNS_DEFAULT_TIMEOUT);
    log_debug_stream(_logger) << "SNS rest module initialized, endpoint: " << _host << ":" << _port << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.sqs.period", 10000);

    // Create environment
    _region = _configuration.getString("awsmock.region");
    log_debug_stream(_logger) << "SNSServer initialized" << std::endl;
  }

  void SNSServer::Initialize() {

    // Check module active
    if (!IsActive("sns")) {
      log_info_stream(_logger) << "SNS module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "SNS module starting" << std::endl;

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SNSRequestHandlerFactory(_configuration, _metricService, _condition));
  }

  void SNSServer::Run() {
    log_trace_stream(_logger) << "S3 processing started" << std::endl;
    UpdateCounters();
  }

  void SNSServer::Shutdown() {
    StopHttpServer();
  }

  void SNSServer::UpdateCounters() {

    // Get total counts
    long topics = _snsDatabase.CountTopics();
    long messages = _snsDatabase.CountMessages();
    _metricService.SetGauge("sns_topic_count_total", topics);
    _metricService.SetGauge("sns_message_count_total", messages);

    // Count messages per topic
    for (const auto &topic : _snsDatabase.ListTopics()) {
      std::string labelValue = Poco::replace(topic.topicName, "-", "_");
      long messagesPerQueue = _snsDatabase.CountMessages(topic.region, topic.topicArn);
      _metricService.SetGauge("sns_message_count", "topic", labelValue, messagesPerQueue);
    }
    log_trace_stream(_logger) << "SNS update counter finished" << std::endl;
  }
} // namespace AwsMock::Worker
