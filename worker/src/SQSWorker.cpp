//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/SQSWorker.h>

namespace AwsMock::Worker {

    SQSWorker::SQSWorker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("SQSWorker")), _configuration(configuration), _running(false) {
        Core::Logger::SetDefaultConsoleLogger("SQSWorker");

        Initialize();

        poco_debug(_logger, "SQSWorker initialized");
    }

    void SQSWorker::Initialize() {

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _sqsDatabase = std::make_unique<Database::SQSDatabase>(_configuration);
        _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);
    }

    void SQSWorker::run() {

        // Check service active
        if (!_serviceDatabase->IsActive("SQS")) {
            return;
        }

        _running = true;
        while (_running) {
            ResetMessages();
            Poco::Thread::sleep(1000);
        }
    }

    void SQSWorker::ResetMessages() {
        Database::Entity::SQS::QueueList queueList = _sqsDatabase->ListQueues(_region);
        for (const auto &q : queueList) {

            // Reset messages which have expired
            _sqsDatabase->ResetMessages(q.queueUrl, q.attributes.visibilityTimeout);

            // Delete messages which are over the retention period
            _sqsDatabase->ResetMessages(q.queueUrl, q.attributes.visibilityTimeout);
        }
    }
} // namespace AwsMock::Worker
