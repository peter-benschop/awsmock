//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SQSClientCommand.h>

namespace AwsMock::Dto::Common {

  void SQSClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "sqs");

    // Basic values
    this->region = region;
    this->user = user;
    this->method = method;
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
    request.stream().seekg(0, request.stream().beg);
    return sstream.str();
  }

  std::string SQSClientCommand::GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) {

    std::string command;
    std::string cType = request["Content-Type"];
    if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-www-form-urlencoded")) {

      command = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

    } else if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-amz-json-1.0")) {

      std::string headerValue = request["X-Amz-Target"];
      command = Core::StringUtils::Split(headerValue, '.')[1];

    }
    return Core::StringUtils::ToSnakeCase(command);
  }

  std::string SQSClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SQSClientCommand &r) {
    os << "SQSClientCommand={method='" << HttpMethodToString(r.method) << ", region='" << r.region << "', user='" << r.user << "', command='" << SqsCommandTypeToString(r.command) << " contentType='" << r.contentType << "' payload='" << r.payload << "'}";
    return os;
  }
}
