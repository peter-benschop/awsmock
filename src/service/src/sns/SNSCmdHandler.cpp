
#include "awsmock/service/sns/SNSCmdHandler.h"

namespace AwsMock::Service {

  SNSCmdHandler::SNSCmdHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _snsService(configuration) {
  }

  void SNSCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::SNSClientCommand &snsClientCommand) {
    log_trace << "SNS POST request, URI: " << request.getURI() << " region: " << snsClientCommand.region << " user: " << snsClientCommand.user << " command: " << Dto::Common::SNSCommandTypeToString(snsClientCommand.command);

    std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

    switch (snsClientCommand.command) {

    case Dto::Common::SNSCommandType::CREATE_TOPIC: {

      std::string name = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Name");
      log_debug << "Topic name: " << name;

      Dto::SNS::CreateTopicRequest snsRequest = {.region=snsClientCommand.region, .topicName = name, .owner=snsClientCommand.user};
      Dto::SNS::CreateTopicResponse snsResponse = _snsService.CreateTopic(snsRequest);
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Topic created, name: " << name;

      break;
    }

    case Dto::Common::SNSCommandType::LIST_TOPICS: {

      Dto::SNS::ListTopicsResponse snsResponse = _snsService.ListTopics(snsClientCommand.region);
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "List topics";

      break;
    }

    case Dto::Common::SNSCommandType::PUBLISH: {

      std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "TopicArn");
      std::string targetArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "TargetArn");
      std::string message = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Message");

      Dto::SNS::PublishResponse snsResponse = _snsService.Publish({.region=snsClientCommand.region, .topicArn=topicArn, .targetArn=targetArn, .message=message});
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Message published, topic: " << topicArn;

      break;
    }

    case Dto::Common::SNSCommandType::SUBSCRIBE: {

      std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "TopicArn");
      std::string protocol = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Protocol");
      std::string endpoint = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Endpoint");

      Dto::SNS::SubscribeResponse snsResponse = _snsService.Subscribe({.region=snsClientCommand.region, .topicArn=topicArn, .protocol=protocol, .endpoint=endpoint, .owner=snsClientCommand.user});
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Subscribed to topic, topicArn: " << topicArn;

      break;
    }

    case Dto::Common::SNSCommandType::UNSUBSCRIBE: {

      std::string subscriptionArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "SubscriptionArn");

      Dto::SNS::UnsubscribeResponse snsResponse = _snsService.Unsubscribe({.region=snsClientCommand.region, .subscriptionArn=subscriptionArn});
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Unsubscribed from topic, subscriptionArn: " << subscriptionArn;

      break;
    }

    case Dto::Common::SNSCommandType::TAG_RESOURCE: {

      std::string resourceArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "ResourceArn");
      log_debug << "Resource ARN: " << resourceArn;

      int count = Core::HttpUtils::CountQueryParametersByPrefix(snsClientCommand.payload, "Tags.member") / 2;
      log_trace << "Got tags count, count: " << count;

      std::map<std::string, std::string> tags;
      for (int i = 1; i <= count; i++) {
        std::string tagKey = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Tags.member." + std::to_string(i) + ".Key");
        std::string tagValue = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "Tags.member." + std::to_string(i) + ".Value");
        tags[tagKey] = tagValue;
      }
      Dto::SNS::TagResourceRequest snsRequest = {.region=snsClientCommand.region, .resourceArn= resourceArn, .tags=tags};
      Dto::SNS::TagResourceResponse snsResponse = _snsService.TagResource(snsRequest);
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Topic tagged, resourceArn: " << resourceArn;

      break;
    }
    case Dto::Common::SNSCommandType::DELETE_TOPIC: {

      std::string topicArn = Core::HttpUtils::GetQueryParameterValueByName(snsClientCommand.payload, "TopicArn");
      log_debug << "Topic ARN: " << topicArn;

      Dto::SNS::DeleteTopicResponse snsResponse = _snsService.DeleteTopic(snsClientCommand.region, topicArn);
      SendOkResponse(response, snsResponse.ToXml());
      log_info << "Topic deleted, topicArn: " << topicArn;

      break;
    }

    case Dto::Common::SNSCommandType::UNKNOWN: {
      log_error << "Bad request, method: POST clientCommand: " << Dto::Common::SNSCommandTypeToString(snsClientCommand.command);
      throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::SNSCommandTypeToString(snsClientCommand.command));
    }
    }
  }
}
