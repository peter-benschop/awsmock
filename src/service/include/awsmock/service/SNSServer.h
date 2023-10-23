//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SNSSERVER_H
#define AWSMOCK_SERVICE_SNSSERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/SNSMonitoring.h>
#include <awsmock/service/SNSHandlerFactory.h>

#define SNS_DEFAULT_PORT 9502
#define SNS_DEFAULT_HOST "localhost"
#define SNS_DEFAULT_QUEUE_LENGTH  250
#define SNS_DEFAULT_THREADS 50

namespace AwsMock::Service {

  class SNSServer : public AbstractServer {

    public:

      /**
       * Constructor
       *
       * @param configuration aws-mock configuration
       * @param metricService aws-mock monitoring service
       * @param condition stop condition
       */
      explicit SNSServer(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition);

      /**
       * Destructor
       */
      ~SNSServer() override;

      /**
       * Main method
       */
      void MainLoop() override;

      /**
       * Stop server
       */
      void StopServer();

      /**
       * Return running flag
       *
       * @return running flag
       */
      bool IsRunning() const { return _running; }

    private:

      /**
       * Start monitoring
       */
      void StartMonitoring();

      /**
       * Start the restfull service.
       */
      void StartHttpServer();

      /**
       * Stop the restfull service
       */
      void StopHttpServer();

      /**
       * Reset messages
       *
       * <p>Loops over all SQS queues and sets the status to INITIAL in case the visibility timeout has been reached. Also the retry count in increased by one.</p>
       * <p>Checks also the expiration date and removed the messages, which are older than the max retention period.</>
       */
      void ResetMessages();

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;

      /**
       * S3 service
       */
      std::unique_ptr<Database::SQSDatabase> _sqsDatabase;

      /**
       * Thread pool
       */
      AwsMock::Core::ThreadPool<SNSMonitoring> _threadPool;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * Running flag
       */
      bool _running;

      /**
       * Sleeping period in ms
       */
      int _period;

      /**
       * Rest port
       */
      int _port;

      /**
       * Rest host
       */
      std::string _host;

      /**
       * HTTP max message queue length
       */
      int _maxQueueLength;

      /**
       * HTTP max concurrent connections
       */
      int _maxThreads;

      /**
       * HTTP server instance
       */
      std::shared_ptr<Poco::Net::HTTPServer> _httpServer;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SNSSERVER_H
