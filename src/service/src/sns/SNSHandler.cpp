
#include <awsmock/service/sns/SNSHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> SNSHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "SNS POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::SNSClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        switch (clientCommand.command) {

            case Dto::Common::SNSCommandType::CREATE_TOPIC: {

                std::string name = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Name");
                log_debug << "Topic name: " << name;

                Dto::SNS::CreateTopicRequest snsRequest = {.region = clientCommand.region, .topicName = name, .owner = clientCommand.user};
                Dto::SNS::CreateTopicResponse snsResponse = _snsService.CreateTopic(snsRequest);
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Topic created, name: " << name;

                break;
            }

            case Dto::Common::SNSCommandType::LIST_TOPICS: {

                Dto::SNS::ListTopicsResponse snsResponse = _snsService.ListTopics(clientCommand.region);
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "List topics";

                break;
            }

            case Dto::Common::SNSCommandType::GET_TOPIC_ATTRIBUTES: {

                std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");

                Dto::SNS::GetTopicAttributesResponse snsResponse = _snsService.GetTopicAttributes({.region = clientCommand.region, .topicArn = topicArn});
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Get topic attributes, topicArn" << topicArn;

                break;
            }

            case Dto::Common::SNSCommandType::PUBLISH: {

                std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                std::string targetArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TargetArn");
                std::string message = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Message");

                Dto::SNS::PublishResponse snsResponse = _snsService.Publish({.region = clientCommand.region, .topicArn = topicArn, .targetArn = targetArn, .message = message});
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Message published, topic: " << topicArn;

                break;
            }

            case Dto::Common::SNSCommandType::SUBSCRIBE: {

                std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                std::string protocol = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Protocol");
                std::string endpoint = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Endpoint");

                Dto::SNS::SubscribeResponse snsResponse = _snsService.Subscribe({.region = clientCommand.region, .topicArn = topicArn, .protocol = protocol, .endpoint = endpoint, .owner = clientCommand.user});
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Subscribed to topic, topicArn: " << topicArn;

                break;
            }

            case Dto::Common::SNSCommandType::UNSUBSCRIBE: {

                std::string subscriptionArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "SubscriptionArn");

                Dto::SNS::UnsubscribeResponse snsResponse = _snsService.Unsubscribe({.region = clientCommand.region, .subscriptionArn = subscriptionArn});
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Unsubscribed from topic, subscriptionArn: " << subscriptionArn;

                break;
            }

            case Dto::Common::SNSCommandType::LIST_SUBSCRIPTIONS_BY_TOPIC: {

                std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");

                Dto::SNS::ListSubscriptionsByTopicResponse snsResponse = _snsService.ListSubscriptionsByTopic({.region = clientCommand.region, .topicArn = topicArn});
                SendOkResponse(request, snsResponse.ToXml());
                log_info << "List subscriptions by topic, topicArn: " << topicArn << " count: " << snsResponse.subscriptions.size();

                break;
            }

            case Dto::Common::SNSCommandType::TAG_RESOURCE: {

                std::string resourceArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "ResourceArn");
                log_debug << "Resource ARN: " << resourceArn;

                int count = Core::HttpUtils::CountQueryParametersByPrefix(clientCommand.payload, "Tags.member") / 2;
                log_trace << "Got tags count, count: " << count;

                std::map<std::string, std::string> tags;
                for (int i = 1; i <= count; i++) {
                    std::string tagKey = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Tags.member." + std::to_string(i) + ".Key");
                    std::string tagValue = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Tags.member." + std::to_string(i) + ".Value");
                    tags[tagKey] = tagValue;
                }
                Dto::SNS::TagResourceRequest snsRequest = {.region = clientCommand.region, .resourceArn = resourceArn, .tags = tags};
                Dto::SNS::TagResourceResponse snsResponse = _snsService.TagResource(snsRequest);
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Topic tagged, resourceArn: " << resourceArn;

                break;
            }
            case Dto::Common::SNSCommandType::DELETE_TOPIC: {

                std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                log_debug << "Topic ARN: " << topicArn;

                Dto::SNS::DeleteTopicResponse snsResponse = _snsService.DeleteTopic(clientCommand.region, topicArn);
                return SendOkResponse(request, snsResponse.ToXml());
                log_info << "Topic deleted, topicArn: " << topicArn;

                break;
            }

            case Dto::Common::SNSCommandType::UNKNOWN: {
                log_error << "Bad request, method: POST clientCommand: " << Dto::Common::SNSCommandTypeToString(clientCommand.command);
                throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::SNSCommandTypeToString(clientCommand.command));
            }
        }
    }

}// namespace AwsMock::Service
