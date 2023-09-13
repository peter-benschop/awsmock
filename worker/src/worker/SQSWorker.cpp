//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/worker/SQSWorker.h"

namespace AwsMock::Worker {

    SQSWorker::SQSWorker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("SQSWorker")), _configuration(configuration), _running(false) {

        Initialize();
    }

    void SQSWorker::Initialize() {

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.sqs.period", 10000);

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _sqsDatabase = std::make_unique<Database::SQSDatabase>(_configuration);
        _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);

        log_debug_stream(_logger) << "SQSWorker initialized" << std::endl;
    }

    void SQSWorker::run() {

        log_info_stream(_logger) << "SQS worker started" << std::endl;

        // Check service active
//        if (!_serviceDatabase->IsActive("SQS")) {
//            return;
//        }

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "SQSWorker processing started" << std::endl;
            ResetMessages();
            Poco::Thread::sleep(_period);
        }
    }

    void SQSWorker::ResetMessages() {

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
            if(!queue.attributes.redrivePolicy.deadLetterTargetArn.empty()) {
                _sqsDatabase->RedriveMessages(queue.queueUrl, queue.attributes.redrivePolicy);
            }

            _sqsDatabase->UpdateQueue(queue);
            log_trace_stream(_logger) << "Queue updated, name" << queue.name << std::endl;
        }
    }
} // namespace AwsMock::Worker
