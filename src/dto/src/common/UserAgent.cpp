//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

  void UserAgent::FromRequest(const Poco::Net::HTTPServerRequest &request) {

    std::string userAgent = request["User-Agent"];
    Poco::RegularExpression::MatchVec posVec;
    Poco::RegularExpression pattern(R"(^([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)+\ ([A-Za-z0-9_\-\/\.]+)\ command\/(.*)\.(.*)$)");
    if (!pattern.match(userAgent, 0, posVec)) {
      throw Core::ServiceException("Could not extract user agent DTO");
    }

    clientApplication = userAgent.substr(posVec[1].offset, posVec[1].length);
    clientLanguage = userAgent.substr(posVec[2].offset, posVec[2].length);
    clientOs = userAgent.substr(posVec[3].offset, posVec[3].length);
    clientExecutableType = userAgent.substr(posVec[4].offset, posVec[4].length);
    clientPrompt = userAgent.substr(posVec[5].offset, posVec[5].length) == "ON";
    clientModule = userAgent.substr(posVec[6].offset, posVec[6].length);
    clientCommand = userAgent.substr(posVec[7].offset, posVec[7].length);

    contentType = Core::StringUtils::Contains(request["Content-Type"], "json") ? "json" : "xml";
  }

  void UserAgent::FromRequest(const Poco::Net::HTTPServerRequest &request, const std::string &service) {
    FromRequest(request);
    if (clientModule != service) {
      throw Core::ServiceException("Request was send to the wrong service!");
    }
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
