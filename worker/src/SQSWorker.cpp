//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/SQSWorker.h>

namespace AwsMock::Worker {

    SQSWorker::SQSWorker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("SQSWorker")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("SQSWorker");

        Initialize();

        poco_debug(_logger, "SQSWorker initialized");
    }

    SQSWorker::~SQSWorker() {
    }

    void SQSWorker::Initialize() {

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _sqsDatabase = std::make_unique<Database::SQSDatabase>(_configuration);
    }

    [[noreturn]] void SQSWorker::run() {

        while (true) {
            ResetMessages();
            Poco::Thread::sleep(1000);
        }
    }

    void SQSWorker::ResetMessages() {
        Database::Entity::SQS::QueueList queueList = _sqsDatabase->ListQueues(_region);
        for(const auto &q:queueList) {

            // Get the queue attributes
            Database::Entity::SQS::QueueAttribute queueAttributes = _sqsDatabase->GetQueueAttributesByQueueUrl(q.queueUrl);

            // Reset messages which have expired
            _sqsDatabase->ResetMessages(q.queueUrl, queueAttributes.visibilityTimeout);

            // Delete messages which are over the retention period
            _sqsDatabase->ResetMessages(q.queueUrl, queueAttributes.visibilityTimeout);
        }
    }
} // namespace AwsMock::Worker
