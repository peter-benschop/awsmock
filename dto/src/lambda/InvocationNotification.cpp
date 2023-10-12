//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/InvocationNotification.h>

namespace AwsMock::Dto::Lambda {

  InvocationNotification::InvocationNotification(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user, const std::string &hostName, int port) {
    this->functionName = functionName;
    this->payload = payload;
    this->region = region;
    this->user = user;
    this->hostName = hostName;
    this->port = port;
  }

  std::string InvocationNotification::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const InvocationNotification &f) {
    os << "InvocationNotification={functionName='" << f.functionName << "', payload='" << f.payload << "', region='" << f.region << "', user='" << f.user << "', hostName: '" << f.hostName << "', port: " << f.port << "}";
    return os;
  }
}
