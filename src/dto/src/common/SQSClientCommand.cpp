//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SQSClientCommand.h>

namespace AwsMock::Dto::Common {

  void SQSClientCommand::FromRequest(const HttpMethod &httpMethod, Poco::Net::HTTPServerRequest &request, const std::string &awsRegion, const std::string &awsUser) {

    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "sqs");

    // Basic values
    this->method = httpMethod;
    this->region = awsRegion;
    this->user = awsUser;
    this->contentType = userAgent.contentType;
    this->payload = GetBodyAsString(request);

    if (userAgent.clientCommand.empty()) {

      this->command = Dto::Common::SqsCommandTypeFromString(GetCommandFromHeader(request));

    } else {

      this->command = Dto::Common::SqsCommandTypeFromString(userAgent.clientCommand);
    }
  }

  std::string SQSClientCommand::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
    std::stringstream sstream;
    sstream << request.stream().rdbuf();
    return sstream.str();
  }

  std::string SQSClientCommand::GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) const {

    std::string cmd;
    std::string cType = request["Content-Type"];
    if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-www-form-urlencoded")) {

      cmd = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

    } else if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-amz-json-1.0")) {

      std::string headerValue = request["X-Amz-Target"];
      cmd = Core::StringUtils::Split(headerValue, '.')[1];

    }
    return Core::StringUtils::ToSnakeCase(cmd);
  }

  std::string SQSClientCommand::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("method", method);
      rootJson.set("region", region);
      rootJson.set("user", user);
      rootJson.set("command", command);
      rootJson.set("contentType", contentType);
      rootJson.set("payload", payload);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string SQSClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SQSClientCommand &r) {
    os << "SQSClientCommand=" << r.ToJson();
    return os;
  }
}
