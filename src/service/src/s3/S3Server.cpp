//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/s3/S3Server.h"

namespace AwsMock::Service {

  S3Server::S3Server(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractWorker(configuration), AbstractServer(configuration, "s3"), _logger(Poco::Logger::get("S3Server")), _configuration(configuration), _metricService(metricService), _module("s3"), _s3Database(Database::S3Database::instance()) {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.s3.port", S3_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.s3.max.queue", S3_DEFAULT_QUEUE_SIZE);
    _maxThreads = _configuration.getInt("awsmock.service.s3.max.threads", S3_DEFAULT_MAX_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.s3.timeout", S3_DEFAULT_TIMEOUT);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.s3.period", 10000);
    log_debug_stream(_logger) << "Worker period: " << _period << std::endl;
    log_debug_stream(_logger) << "S3 module initialized, endpoint: " << _host << ":" << _port << std::endl;
  }

  S3Server::~S3Server() {
    StopServer();
  }

  void S3Server::MainLoop() {

    // Check module active
    if (!IsActive("s3")) {
      log_info_stream(_logger) << "S3 module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "S3 module starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new S3RequestHandlerFactory(_configuration, _metricService));

    while (IsRunning()) {

      log_trace_stream(_logger) << "S3 processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        break;
      }
      UpdateCounters();
    }
  }

  void S3Server::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void S3Server::StopMonitoringServer() {
    _threadPool.stopAll();
    log_debug_stream(_logger) << "Monitoring stopped module: s3" << std::endl;
  }

  void S3Server::UpdateCounters() {
    long buckets = _s3Database.BucketCount();
    long objects = _s3Database.ObjectCount();
    _metricService.SetGauge("s3_bucket_count", buckets);
    _metricService.SetGauge("s3_object_count", objects);
  }
}
