
#include <awsmock/service/sns/SNSHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> SNSHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "SNS POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {

            Dto::Common::SNSClientCommand clientCommand;
            clientCommand.FromRequest(request, region, user);

            switch (clientCommand.command) {

                case Dto::Common::SNSCommandType::CREATE_TOPIC: {

                    std::string name = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Name");
                    log_debug << "Topic name: " << name;

                    Dto::SNS::CreateTopicRequest snsRequest = {.region = clientCommand.region, .topicName = name, .owner = clientCommand.user};
                    Dto::SNS::CreateTopicResponse snsResponse = _snsService.CreateTopic(snsRequest);

                    log_info << "Topic created, name: " << name;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::LIST_TOPICS: {

                    Dto::SNS::ListTopicsResponse snsResponse = _snsService.ListTopics(clientCommand.region);

                    log_info << "List topics";
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::LIST_TOPIC_COUNTERS: {

                    Dto::SNS::ListTopicCountersRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);
                    snsRequest.region = region;

                    Dto::SNS::ListTopicCountersResponse snsResponse = _snsService.ListTopicCounters(snsRequest);

                    log_info << "List topics";
                    return SendOkResponse(request, snsResponse.ToJson());
                }

                case Dto::Common::SNSCommandType::GET_TOPIC_ATTRIBUTES: {

                    std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");

                    Dto::SNS::GetTopicAttributesResponse snsResponse = _snsService.GetTopicAttributes({.region = clientCommand.region, .topicArn = topicArn});

                    log_info << "Get topic attributes, topicArn" << topicArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::GET_TOPIC_DETAILS: {

                    Dto::SNS::GetTopicDetailsRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);

                    Dto::SNS::GetTopicDetailsResponse snsResponse = _snsService.GetTopicDetails(snsRequest);

                    log_info << "Get topic details, topicArn" << snsRequest.topicArn;
                    return SendOkResponse(request, snsResponse.ToJson());
                }

                case Dto::Common::SNSCommandType::PUBLISH: {

                    std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                    std::string targetArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TargetArn");
                    std::string message = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Message");

                    Dto::SNS::PublishResponse snsResponse = _snsService.Publish({.region = clientCommand.region, .topicArn = topicArn, .targetArn = targetArn, .message = message, .requestId = clientCommand.requestId});

                    std::map<std::string, std::string> headers;
                    headers["Content-Type"] = "application/xml";
                    headers["Content-Length"] = std::to_string(snsResponse.ToXml().length());
                    headers["amz-sdk-invocation-id"] = snsResponse.requestId;

                    log_info << "Message published, topic: " << topicArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::SUBSCRIBE: {

                    std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                    std::string protocol = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Protocol");
                    std::string endpoint = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Endpoint");

                    Dto::SNS::SubscribeResponse snsResponse = _snsService.Subscribe({.region = clientCommand.region, .topicArn = topicArn, .protocol = protocol, .endpoint = endpoint, .owner = clientCommand.user});

                    log_info << "Subscribed to topic, topicArn: " << topicArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::UNSUBSCRIBE: {

                    std::string subscriptionArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "SubscriptionArn");

                    Dto::SNS::UnsubscribeResponse snsResponse = _snsService.Unsubscribe({.region = clientCommand.region, .subscriptionArn = subscriptionArn});

                    log_info << "Unsubscribed from topic, subscriptionArn: " << subscriptionArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::LIST_SUBSCRIPTIONS_BY_TOPIC: {

                    std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");

                    Dto::SNS::ListSubscriptionsByTopicResponse snsResponse = _snsService.ListSubscriptionsByTopic({.region = clientCommand.region, .topicArn = topicArn});
                    log_info << "List subscriptions by topic, topicArn: " << topicArn << " count: " << snsResponse.subscriptions.size();
                    return SendOkResponse(request, snsResponse.ToXml());
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

                    log_info << "Topic tagged, resourceArn: " << resourceArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::PURGE_TOPIC: {

                    Dto::SNS::PurgeTopicRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);
                    log_debug << "Purge topic, topicArn: " << snsRequest.topicArn;

                    _snsService.PurgeTopic(snsRequest);

                    log_info << "Topic purged, topicArn: " << snsRequest.topicArn;
                    return SendOkResponse(request);
                }

                case Dto::Common::SNSCommandType::DELETE_TOPIC: {

                    std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "TopicArn");
                    log_debug << "Topic ARN: " << topicArn;

                    Dto::SNS::DeleteTopicResponse snsResponse = _snsService.DeleteTopic(clientCommand.region, topicArn);

                    log_info << "Topic deleted, topicArn: " << topicArn;
                    return SendOkResponse(request, snsResponse.ToXml());
                }

                case Dto::Common::SNSCommandType::LIST_MESSAGES: {

                    Dto::SNS::ListMessagesRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);
                    snsRequest.region = region;

                    log_debug << "List messages, payload: " << clientCommand.payload;
                    log_debug << "List messages, topicArn: " << snsRequest.topicArn;

                    Dto::SNS::ListMessagesResponse snsResponse = _snsService.ListMessages(snsRequest);

                    log_info << "List messages, topicArn: " << snsRequest.topicArn << " count: " << snsResponse.messageList.size();
                    return SendOkResponse(request, snsResponse.ToJson());
                }

                case Dto::Common::SNSCommandType::DELETE_MESSAGE: {

                    Dto::SNS::DeleteMessageRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);

                    _snsService.DeleteMessage(snsRequest);

                    log_info << "Message deleted, messageId: " << snsRequest.messageId;
                    return SendOkResponse(request, "{}");
                }

                case Dto::Common::SNSCommandType::LIST_SUBSCRIPTION_COUNTERS: {

                    Dto::SNS::ListSubscriptionCountersRequest snsRequest;
                    snsRequest.FromJson(clientCommand.payload);

                    Dto::SNS::ListSubscriptionCountersResponse snsResponse = _snsService.ListSubscriptionCounters(snsRequest);

                    log_info << "List subscriptions counters, topicArn: " << snsRequest.topicArn << " count: " << snsResponse.subscriptionCounters.size();
                    return SendOkResponse(request, snsResponse.ToJson());
                }

                default:
                case Dto::Common::SNSCommandType::UNKNOWN: {
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
                }
            }

        } catch (Poco::Exception &e) {
            log_error << e.message();
            return Core::HttpUtils::InternalServerError(request, e.message());
        }
    }

}// namespace AwsMock::Service
