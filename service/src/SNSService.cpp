//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/SNSService.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    SNSService::SNSService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("SNSService")), _configuration(configuration) {
        Initialize();
    }

    void SNSService::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("SNSService");

        // Initialize environment
        _database = std::make_unique<Database::SNSDatabase>(_configuration);
        _accountId = DEFAULT_ACCOUNT_ID;
    }

    Dto::SNS::CreateTopicResponse SNSService::CreateTopic(const Dto::SNS::CreateTopicRequest &request) {
        _logger.trace() << "Create topic request: " << request.ToString();

        Database::Entity::SNS::Topic topic;
        try {
            // Check existence
            if (_database->TopicExists(request.region, request.topicName)) {
                throw Core::ServiceException("SQS Queue exists already", 500);
            }

            // Update database
            std::string topicArn = Core::AwsUtils::CreateSNSArn(request.region, _accountId, request.topicName);
            topic = _database->CreateTopic({.region=request.region, .topicName=request.topicName, .owner=request.owner, .topicArn=topicArn});
            _logger.trace() << "SNS topic created: " << topic.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "SNS create topic failed, message: " << exc.message();
            throw Core::ServiceException(exc.message(), 500);
        }
        return {.region=topic.region, .name=topic.topicName, .owner=topic.owner, .topicArn=topic.topicArn};
    }

    Dto::SNS::ListTopicsResponse SNSService::ListTopics(const std::string &region) {
        _logger.trace() << "List all topics request, region: " << region;

        try {

            Database::Entity::SNS::TopicList topicList = _database->ListTopics(region);
            auto listTopicsResponse = Dto::SNS::ListTopicsResponse(topicList);
            _logger.trace() << "SNS list topics response: " << listTopicsResponse.ToXml();

            return listTopicsResponse;

        } catch (Poco::Exception &ex) {
            _logger.error() << "SNS list topics request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500, "SQS", Poco::UUIDGenerator().createRandom().toString().c_str());
        }
    }

    Dto::SNS::DeleteTopicResponse SNSService::DeleteTopic(const std::string &region, const std::string &topicArn) {
        _logger.trace() << "Delete topic request, region: " << region << " topicArn: " << topicArn;

        Dto::SNS::DeleteTopicResponse response;
        try {
            // Check existence
            if (!_database->TopicExists(topicArn)) {
                throw Core::ServiceException("Topic does not exist", 500);
            }

            // Update database
            _database->DeleteTopic({.region=region, .topicArn=topicArn});

        } catch (Poco::Exception &ex) {
            _logger.error() << "SNS delete topic failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
        return response;
    }

    Dto::SNS::PublishResponse SNSService::Publish(const Dto::SNS::PublishRequest &request) {

        Database::Entity::SNS::Message message;
        try {
            // Check topic/target ARN
            if (request.topicArn.empty() && request.targetArn.empty()) {
                throw Core::ServiceException("Either topicARN or targetArn must exist", 500);
            }

            // Check existence
            if (!_database->TopicExists(request.topicArn)) {
                throw Core::ServiceException("SNS topic does not exists", 500);
            }

            // Update database
            std::string messageId = Core::StringUtils::GenerateRandomString(100);
            message =
                _database->CreateMessage({.region=request.region, .topicArn=request.topicArn, .targetArn=request.targetArn, .message=request.message, .messageId=messageId});

            return {.messageId=message.messageId};

        } catch (Poco::Exception &ex) {
            _logger.error() << "SQS create message failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
    }

} // namespace AwsMock::Service
