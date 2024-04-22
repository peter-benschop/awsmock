//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SNSClientCommand.h>

namespace AwsMock::Dto::Common {

  void SNSClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "sqs");

    // Basic values
    this->region = region;
    this->user = user;
    this->method = method;
    this->contentType = userAgent.contentType;
    this->payload = GetBodyAsString(request);

    if (userAgent.clientCommand.empty()) {

      this->command = Dto::Common::SNSCommandTypeFromString(GetCommandFromHeader(request));

    } else {

      this->command = Dto::Common::SNSCommandTypeFromString(userAgent.clientCommand);
    }
  }

  std::string SNSClientCommand::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
    std::stringstream sstream;
    sstream << request.stream().rdbuf();
    request.stream().seekg(0, request.stream().beg);
    return sstream.str();
  }

  std::string SNSClientCommand::GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) const {

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

  std::string SNSClientCommand::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("method", HttpMethodToString(method));
      rootJson.set("command", SNSCommandTypeToString(command));
      rootJson.set("user", user);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string SNSClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SNSClientCommand &r) {
    os << "SNSClientCommand={method='" << HttpMethodToString(r.method) << ", region='" << r.region << "', user='" << r.user << "', command='" << SNSCommandTypeToString(r.command) << " contentType='" << r.contentType << "' payload='" << r.payload << "'}";
    return os;
  }
}
