//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/SQSServer.h>

namespace AwsMock::Service {

  SQSServer::SQSServer(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
      : AbstractServer(configuration, condition), _logger(Poco::Logger::get("SQSServer")), _configuration(configuration), _metricService(metricService), _running(false) {

    // HTTP server configuration
    _port = _configuration.getInt("awsmock.service.sqs.port", SQS_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.sqs.host", SQS_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.sqs.max.queue", SQS_DEFAULT_QUEUE_LENGTH);
    _maxThreads = _configuration.getInt("awsmock.service.sqs.max.threads", SQS_DEFAULT_THREADS);
    log_debug_stream(_logger) << "SQS rest service initialized, endpoint: " << _host << ":" << _port << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.sqs.period", 10000);

    // Create environment
    _region = _configuration.getString("awsmock.region");
    _sqsDatabase = std::make_unique<Database::SQSDatabase>(_configuration);
    _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);
    log_debug_stream(_logger) << "SQSServer initialized" << std::endl;
  }

  SQSServer::~SQSServer() {
    StopServer();
    _condition.signal();
  }

  void SQSServer::MainLoop() {

    // Check service active
    if (!IsActive("sqs")) {
      log_info_stream(_logger) << "SQS service inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "SQS worker starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST service
    StartHttpServer();

    _running = true;
    while (_running) {

      log_debug_stream(_logger) << "SQSServer processing started" << std::endl;

      // Reset messages
      ResetMessages();

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        break;
      }
    }

    // Shutdown
    StopServer();
  }

  void SQSServer::StopServer() {
    _running = false;
    StopHttpServer();
    _threadPool.stopAll();
  }

  void SQSServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void SQSServer::StartHttpServer() {

    // Set HTTP server parameter
    auto *httpServerParams = new Poco::Net::HTTPServerParams();
    httpServerParams->setMaxQueued(_maxQueueLength);
    httpServerParams->setMaxThreads(_maxThreads);
    log_debug_stream(_logger) << "HTTP server parameter set, maxQueue: " << _maxQueueLength << " maxThreads: " << _maxThreads << std::endl;

    _httpServer = std::make_shared<Poco::Net::HTTPServer>(new SQSRequestHandlerFactory(_configuration, _metricService, _condition), Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

    _httpServer->start();
    log_info_stream(_logger) << "SQS rest service started, endpoint: http://" << _host << ":" << _port << std::endl;
  }

  void SQSServer::StopHttpServer() {
    if (_httpServer) {
      _httpServer->stopAll(true);
      _httpServer.reset();
      log_info_stream(_logger) << "SQS rest service stopped" << std::endl;
    }
  }

  void SQSServer::ResetMessages() {

    Database::Entity::SQS::QueueList queueList = _sqsDatabase->ListQueues(_region);
    log_trace_stream(_logger) << "Working on queue list, count" << queueList.size() << std::endl;

    for (auto &queue : queueList) {

      // Reset messages which have expired
      _sqsDatabase->ResetMessages(queue.queueUrl, queue.attributes.visibilityTimeout);

      // Set counter default attributes
      queue.attributes.approximateNumberOfMessages = _sqsDatabase->CountMessages(queue.region, queue.queueUrl);
      queue.attributes.approximateNumberOfMessagesDelayed = _sqsDatabase->CountMessagesByStatus(queue.region, queue.queueUrl, Database::Entity::SQS::DELAYED);
      queue.attributes.approximateNumberOfMessagesNotVisible = _sqsDatabase->CountMessagesByStatus(queue.region, queue.queueUrl, Database::Entity::SQS::SEND);

      // Check retries
      if (!queue.attributes.redrivePolicy.deadLetterTargetArn.empty()) {
        _sqsDatabase->RedriveMessages(queue.queueUrl, queue.attributes.redrivePolicy);
      }

      _sqsDatabase->UpdateQueue(queue);
      log_trace_stream(_logger) << "Queue updated, name" << queue.name << std::endl;
    }
  }
} // namespace AwsMock::Worker
