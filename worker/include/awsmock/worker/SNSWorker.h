//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_WORKER_SNSWORKER_H
#define AWSMOCK_WORKER_SNSWORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/worker/SNSMonitoring.h>

namespace AwsMock::Worker {

  class SNSWorker : public Poco::Runnable {

    public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring service
     */
    explicit SNSWorker(const Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Main method
     */
    void run() override;

    private:

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
    const Core::Configuration &_configuration;

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
  };

} // namespace AwsMock::Worker

#endif // AWSMOCK_WORKER_S3WORKER_H
