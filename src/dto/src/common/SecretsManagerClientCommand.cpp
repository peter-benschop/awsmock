//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SecretsManagerClientCommand.h>

namespace AwsMock::Dto::Common {

  void SecretsManagerClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "secretsmanager");

    // Basic values
    this->region = region;
    this->user = user;
    this->method = method;
    this->payload = GetBodyAsString(request);

    // Command
    std::string action = request.get("X-Amz-Target");

    switch (method) {
      case HttpMethod::GET:
      case HttpMethod::PUT:
      case HttpMethod::DELETE:break;
      case HttpMethod::POST:
        if (Core::StringUtils::ContainsIgnoreCase(action, "CreateSecret")) {
          command = SecretsManagerCommandType::CREATE_SECRET;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "DeleteSecret")) {
          command = SecretsManagerCommandType::DELETE_SECRET;
        }
        break;
      case HttpMethod::UNKNOWN: {
        break;
      }
    }
  }

  std::string SecretsManagerClientCommand::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
    std::stringstream sstream;
    sstream << request.stream().rdbuf();
    request.stream().seekg(0, request.stream().beg);
    return sstream.str();
  }

  std::string SecretsManagerClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SecretsManagerClientCommand &r) {
    os << "SecretsManagerClientCommand={method='" << HttpMethodToString(r.method) << ", region='" << r.region << "', user='" << r.user << "', command='" << SecretsManagerCommandTypeToString(r.command) << "}";
    return os;
  }
}
