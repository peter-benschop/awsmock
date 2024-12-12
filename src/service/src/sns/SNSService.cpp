//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/sns/SNSService.h>

namespace AwsMock::Service {

    Dto::SNS::CreateTopicResponse SNSService::CreateTopic(const Dto::SNS::CreateTopicRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "create_topic");
        log_trace << "Create topic request: " << request.ToString();

        // Check existence
        if (_snsDatabase.TopicExists(request.region, request.topicName)) {
            log_warning << "SNS topic '" + request.topicName + "' exists already";
            const Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByName(request.region, request.topicName);
            log_debug << "Got topic: " << topic.topicArn;
            return {
                    .region = topic.region,
                    .name = topic.topicName,
                    .owner = topic.owner,
                    .topicArn = topic.topicArn};
        }

        try {
            // Update database
            const std::string accountId = Core::Configuration::instance().GetValueString("awsmock.access.account-id");
            const std::string topicArn = Core::AwsUtils::CreateSNSTopicArn(request.region, accountId, request.topicName);
            Database::Entity::SNS::Topic topic = {.region = request.region, .topicName = request.topicName, .owner = request.owner, .topicArn = topicArn};
            topic = _snsDatabase.CreateTopic(topic);
            log_trace << "SNS topic created: " << topic.ToString();

            return {.region = topic.region, .name = topic.topicName, .owner = topic.owner, .topicArn = topic.topicArn};

        } catch (Core::DatabaseException &exc) {
            log_error << "SNS create topic failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    Dto::SNS::ListTopicsResponse SNSService::ListTopics(const std::string &region) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "list_topics");
        log_trace << "List all topics request, region: " << region;

        try {

            const Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics(region);
            auto listTopicsResponse = Dto::SNS::ListTopicsResponse(topicList);
            log_trace << "SNS list topics response: " << listTopicsResponse.ToXml();

            return listTopicsResponse;

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS list topics request failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::ListTopicCountersResponse SNSService::ListTopicCounters(const Dto::SNS::ListTopicCountersRequest &request) const {
        Monitoring::MetricServiceTimer measure(SQS_SERVICE_TIMER, "method", "list_topic_counters");
        log_trace << "List all topics counters request, request: " << request.ToString();

        try {

            Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics(request.prefix, request.pageSize, request.pageIndex, request.sortColumns, request.region);

            Dto::SNS::ListTopicCountersResponse listTopicResponse;
            listTopicResponse.total = _snsDatabase.CountTopics(request.region, request.prefix);
            for (const auto &topic: topicList) {
                Dto::SNS::TopicCounter counter;
                counter.topicName = topic.topicName;
                counter.topicArn = topic.topicArn;
                counter.topicUrl = topic.topicUrl;
                counter.availableMessages = topic.topicAttribute.availableMessages;
                counter.created = topic.created;
                counter.modified = topic.modified;
                listTopicResponse.topicCounters.emplace_back(counter);
            }
            log_trace << "SNS list topic counters response: " << listTopicResponse.ToJson();
            return listTopicResponse;

        } catch (bsoncxx::exception &ex) {
            log_error << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    void SNSService::PurgeTopic(const Dto::SNS::PurgeTopicRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "purge_topic");
        log_trace << "Purge topic request, topicArn: " << request.topicArn;

        // Check existence
        if (!_snsDatabase.TopicExists(request.topicArn)) {
            log_warning << "Topic does not exist, topicArn: " << request.topicArn;
            throw Core::NotFoundException("Topic does not exist, topicArn" + request.topicArn);
        }

        try {
            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);
            log_debug << "Got topic: " << topic.topicArn;

            // Update database
            _snsDatabase.PurgeTopic(topic);

            // Adjust topic counters
            AdjustTopicCounters(topic);

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS purge topic failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::DeleteTopicResponse SNSService::DeleteTopic(const std::string &region, const std::string &topicArn) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "delete_topic");
        log_trace << "Delete topic request, region: " << region << " topicArn: " << topicArn;

        // Check existence
        if (!_snsDatabase.TopicExists(topicArn)) {
            log_warning << "Topic does not exist, arn: " << topicArn;
            throw Core::NotFoundException("Topic does not exist");
        }

        Dto::SNS::DeleteTopicResponse response;
        try {

            // Update database
            _snsDatabase.DeleteTopic({.region = region, .topicArn = topicArn});

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS delete topic failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
        return response;
    }

    Dto::SNS::PublishResponse SNSService::Publish(const Dto::SNS::PublishRequest &request) {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "publish");
        log_trace << "Publish message request: " << request.ToString();

        // Check topic/target ARN
        if (request.topicArn.empty()) {
            log_error << "Either topicARN or targetArn must exist";
            throw Core::ServiceException("Either topicARN or targetArn must exist");
        }

        // Check existence
        if (!_snsDatabase.TopicExists(request.topicArn)) {
            log_error << "Topic does not exist: " << request.topicArn;
            throw Core::ServiceException("SNS topic does not exists");
        }

        Database::Entity::SNS::Message message;
        try {

            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);

            // Update database
            std::string messageId = Core::AwsUtils::CreateMessageId();
            message = {.region = request.region,
                       .topicArn = request.topicArn,
                       .targetArn = request.targetArn,
                       .message = request.message,
                       .messageId = messageId,
                       .size = static_cast<long>(request.message.length())};
            message = _snsDatabase.CreateMessage(message);

            // Check subscriptions
            CheckSubscriptions(request);

            // Adjust message counters
            AdjustTopicCounters(topic);

            return {.messageId = message.messageId, .requestId = request.requestId};

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS create message failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::SubscribeResponse SNSService::Subscribe(const Dto::SNS::SubscribeRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "subscribe");
        log_trace << "Subscribe request: " << request.ToString();

        try {

            // Check topic/target ARN
            if (request.topicArn.empty()) {
                log_error << "Topic ARN missing";
                throw Core::ServiceException("Topic ARN missing");
            }

            // Check existence
            if (!_snsDatabase.TopicExists(request.topicArn)) {
                log_error << "SNS topic does not exists";
                throw Core::ServiceException("SNS topic does not exists");
            }

            // Create new subscription
            const std::string accountId = Core::Configuration::instance().GetValueString("awsmock.access.account-id");
            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);
            const std::string subscriptionArn = Core::AwsUtils::CreateSNSSubscriptionArn(request.region, accountId, topic.topicName);

            if (const Database::Entity::SNS::Subscription subscription = {.protocol = request.protocol, .endpoint = request.endpoint}; !topic.HasSubscription(subscription)) {

                // Add subscription
                topic.subscriptions.push_back({.protocol = request.protocol,
                                               .endpoint = request.endpoint,
                                               .subscriptionArn = subscriptionArn});

                // Save to database
                topic = _snsDatabase.UpdateTopic(topic);
                log_debug << "Subscription added, topic: " << topic.ToString();
            }

            return {.subscriptionArn = subscriptionArn};

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS subscription failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::UnsubscribeResponse SNSService::Unsubscribe(const Dto::SNS::UnsubscribeRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "unsubscribe");
        log_trace << "Unsubscribe request: " << request.ToString();

        try {

            // Check topic/target ARN
            if (request.subscriptionArn.empty()) {
                log_error << "Subscription ARN missing";
                throw Core::ServiceException("Subscription ARN missing");
            }

            // Create new subscription
            Database::Entity::SNS::TopicList topics = _snsDatabase.GetTopicsBySubscriptionArn(request.subscriptionArn);

            for (auto &topic: topics) {

                // Remove subscription
                const auto count = std::erase_if(topic.subscriptions, [request](const auto &item) {
                    return item.subscriptionArn == request.subscriptionArn;
                });
                log_debug << "Subscription removed, count" << count;

                // Save to database
                topic = _snsDatabase.UpdateTopic(topic);
                log_debug << "Subscription added, topic: " << topic.ToString();
            }

            return {.subscriptionArn = request.subscriptionArn};

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS subscription failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::ListSubscriptionsByTopicResponse SNSService::ListSubscriptionsByTopic(const Dto::SNS::ListSubscriptionsByTopicRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "list_subscriptions");
        log_trace << "List subscriptions request: " << request.ToString();

        // Check existence
        if (!_snsDatabase.TopicExists(request.topicArn)) {
            log_error << "SNS topic does not exists, topicArn: " << request.topicArn;
            throw Core::ServiceException("SNS topic does not exists, topicArn: " + request.topicArn);
        }

        try {

            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);

            Dto::SNS::ListSubscriptionsByTopicResponse response;
            for (const auto &[protocol, endpoint, subscriptionArn]: topic.subscriptions) {
                Dto::SNS::Subscription subscription = {.topicArn = request.topicArn, .protocol = protocol, .subscriptionArn = subscriptionArn, .endpoint = endpoint};
                response.subscriptions.emplace_back(subscription);
                response.nextToken = subscription.id;
            }
            return response;

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS get topic subscriptions failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::ListSubscriptionCountersResponse SNSService::ListSubscriptionCounters(const Dto::SNS::ListSubscriptionCountersRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "list_subscription_counters");
        log_trace << "List subscription counters request: " << request.ToString();

        // Check existence
        if (!_snsDatabase.TopicExists(request.topicArn)) {
            log_error << "SNS topic does not exists, topicArn: " << request.topicArn;
            throw Core::ServiceException("SNS topic does not exists, topicArn: " + request.topicArn);
        }

        try {

            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);

            Dto::SNS::ListSubscriptionCountersResponse response;
            for (const auto &s: topic.subscriptions) {
                Dto::SNS::Subscription subscription = {.topicArn = request.topicArn, .protocol = s.protocol, .subscriptionArn = s.subscriptionArn, .endpoint = s.endpoint};
                response.subscriptionCounters.emplace_back(subscription);
            }
            return response;

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS get subscription counters failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::GetTopicAttributesResponse SNSService::GetTopicAttributes(const Dto::SNS::GetTopicAttributesRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "get_topic_attributes");
        log_trace << "Get topic attributes request: " << request.ToString();

        try {

            // Check existence
            if (!_snsDatabase.TopicExists(request.topicArn)) {
                throw Core::ServiceException("SNS topic does not exists");
            }

            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);
            return {
                    .region = topic.region,
                    .topicArn = topic.topicArn,
                    .owner = topic.owner};

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS get topic attributes failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    Dto::SNS::GetTopicDetailsResponse SNSService::GetTopicDetails(const Dto::SNS::GetTopicDetailsRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "get_topic_details");
        log_trace << "Get topic details request: " << request.ToString();

        try {

            // Check existence
            if (!_snsDatabase.TopicExists(request.topicArn)) {
                log_error << "SNS topic does not exists, topicArn: " << request.topicArn;
                throw Core::ServiceException("SNS topic does not exists, topicArn: " + request.topicArn);
            }

            const long messageCount = _snsDatabase.CountMessages(request.topicArn);
            const long messagesSize = _snsDatabase.CountMessagesSize(request.topicArn);

            const Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);
            return {
                    .region = topic.region,
                    .topicName = topic.topicName,
                    .topicArn = topic.topicArn,
                    .messageCount = messageCount,
                    .size = messagesSize,
                    .owner = topic.owner,
                    .created = topic.created,
                    .modified = topic.modified,
            };

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS get topic attributes failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    void SNSService::CheckSubscriptions(const Dto::SNS::PublishRequest &request) {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "check_subscriptions");
        log_trace << "Check subscriptions request: " << request.ToString();

        if (const Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn); !topic.subscriptions.empty()) {

            for (const auto &it: topic.subscriptions) {

                if (Poco::toLower(it.protocol) == SQS_PROTOCOL) {

                    SendSQSMessage(it, request);
                    log_debug << "Message send to SQS queue, queueArn: " << it.endpoint;
                }
            }
        }
    }

    Dto::SNS::TagResourceResponse SNSService::TagResource(const Dto::SNS::TagResourceRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "tag_topic");
        log_trace << "Tag topic request: " << request.ToString();

        try {

            // Check existence
            if (!_snsDatabase.TopicExists(request.resourceArn)) {
                log_error << "SNS topic does not exists, topicArn: " << request.resourceArn;
                throw Core::ServiceException("SNS topic does not exists, topicArn: " + request.resourceArn);
            }

            // Get the topic
            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.resourceArn);

            // Set tags and update database
            topic.tags = request.tags;
            _snsDatabase.UpdateTopic(topic);
            log_info << "SNS tags updated, count: " << request.tags.size();

            return {};

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS tag resource failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    void SNSService::SendSQSMessage(const Database::Entity::SNS::Subscription &subscription, const Dto::SNS::PublishRequest &request) {
        log_debug << "Send to SQS queue, queueUrl: " << subscription.endpoint;

        // Get queue by ARN
        const Database::Entity::SQS::Queue sqsQueue = _sqsDatabase.GetQueueByArn(subscription.endpoint);
        log_debug << "Found queue, queueUrl: " << sqsQueue.name;

        // Create a SQS notification request
        const Dto::SNS::SqsNotificationRequest sqsNotificationRequest = {
                .type = "Notification",
                .messageId = Core::AwsUtils::CreateMessageId(),
                .topicArn = request.topicArn,
                .message = request.message,
                .timestamp = Core::DateTimeUtils::UnixTimestamp(std::chrono::system_clock::now())};

        // Wrap it in a SQS message request
        const Dto::SQS::SendMessageRequest sendMessageRequest = {
                .region = request.region,
                .queueUrl = sqsQueue.queueUrl,
                .queueArn = sqsQueue.queueArn,
                .body = sqsNotificationRequest.ToJson(),
                .messageId = Core::AwsUtils::CreateMessageId(),
                .requestId = Core::AwsUtils::CreateRequestId(),
        };

        _sqsService.SendMessage(sendMessageRequest);
    }

    Dto::SNS::ListMessagesResponse SNSService::ListMessages(const Dto::SNS::ListMessagesRequest &request) const {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "list_messages");
        log_trace << "List all messages request, region: " << request.region << " topicArn: " << request.topicArn;

        try {

            const long total = _snsDatabase.CountMessages(request.topicArn);

            const Database::Entity::SNS::MessageList messageList = _snsDatabase.ListMessages(request.region, request.topicArn, request.pageSize, request.pageIndex);

            Dto::SNS::ListMessagesResponse listMessageResponse = Dto::SNS::Mapper::map(request, messageList);
            listMessageResponse.total = total;
            log_trace << "SNS list messages, response: " << listMessageResponse.ToJson();

            return listMessageResponse;

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS list topics request failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    void SNSService::DeleteMessage(const Dto::SNS::DeleteMessageRequest &request) {
        Monitoring::MetricServiceTimer measure(SNS_SERVICE_TIMER, "method", "delete_message");
        log_trace << "Delete a message request, messageId: " << request.messageId;

        if (!_snsDatabase.MessageExists(request.messageId)) {
            log_error << "SNS message does not exists, messageId: " << request.messageId;
            throw Core::ServiceException("SNS message does not exists, messageId: " + request.messageId);
        }

        try {

            _snsDatabase.DeleteMessage(request.messageId);
            log_trace << "SNS message deleted, messageId: " << request.messageId;

            Database::Entity::SNS::Topic topic = _snsDatabase.GetTopicByArn(request.topicArn);

            // Adjust topic counters
            AdjustTopicCounters(topic);
            log_trace << "SNS topci counter adjusted, topicArn: " << request.topicArn;

        } catch (bsoncxx::exception &ex) {
            log_error << "SNS list topics request failed, message: " << ex.what();
            throw Core::ServiceException(ex.what());
        }
    }

    void SNSService::AdjustTopicCounters(Database::Entity::SNS::Topic &topic) const {
        topic.topicAttribute.availableMessages = _snsDatabase.CountMessages(topic.topicArn);
        topic = _snsDatabase.UpdateTopic(topic);
        log_debug << "Topic counters updated, queue: " << topic.topicArn;
    }

}// namespace AwsMock::Service
