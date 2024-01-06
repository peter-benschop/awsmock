//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

  void UserAgent::FromRequest(Poco::Net::HTTPServerRequest &request) {

    if(!request.has("User-Agent")) {

      // C++ does not send a user agent
      type = UserAgentType::AWS_SDK_CPP;
      contentType = "xml";
      return;
    }

    // We have a user agent, so use it
    std::vector<std::string> parts = Core::StringUtils::Split(request["User-Agent"], ' ');
    if (parts.empty() || parts.size() < 4) {
      throw Core::ServiceException("Could not extract user agent DTO");
    } else {

      type = UserAgentTypeFromString(parts[0]);
      if (type == UserAgentType::AWS_CLI) {

        clientApplication = parts[0];
        clientLanguage = parts[1];
        clientOs = parts[2];
        clientExecutableType = parts[3];
        clientPrompt = parts[4] == "ON";
        clientModule = Core::StringUtils::Split(parts[5], '.')[0];
        clientCommand = Core::StringUtils::Split(parts[5], '.')[1];

      }
    }
    if (request.has("Content-Type")) {
      contentType = Core::StringUtils::Contains(request["Content-Type"], "json") ? "json" : "xml";
    }
  }

  void UserAgent::FromRequest(Poco::Net::HTTPServerRequest &request, const std::string &service) {
    FromRequest(request);
  }

  std::string UserAgent::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UserAgent &r) {
    os << "UserAgent={clientApplication='" << r.clientApplication << ", clientLanguage='" << r.clientLanguage << "', clientOs='" << r.clientOs << "', clientExecutableType='" << r.clientExecutableType << "', clientPrompt=" << r.clientPrompt
       << ", clientModule='" << r.clientModule << "', clientCommand='" << r.clientCommand << "' contentType='" << r.contentType << "'}";
    return os;
  }
}
