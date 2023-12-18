//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/Server.h>

namespace AwsMock::Dto::Transfer {

  Poco::JSON::Object Server::ToJsonObject() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Arn", arn);
      rootJson.set("Domain", domain);
      rootJson.set("IdentityProviderType", identityProviderType);
      rootJson.set("EndpointType", endpointType);
      rootJson.set("LoggingRole", loggingRole);
      rootJson.set("ServerId", serverId);
      rootJson.set("State", state);
      rootJson.set("UserCount", userCount);

      return rootJson;

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }

  }

  std::string Server::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Server &r) {
    os << "Server={arn='" << r.arn << "' domain='" << r.domain << "' identityProviderType='" << r.identityProviderType << "' endpointType='" << r.endpointType
       << "' loggingRole='" << r.loggingRole << "' serverId='" << r.serverId << "' state='" << r.state << "' userCount='" << r.userCount << "'}";
    return os;
  }

} // namespace AwsMock::Dto::Transfer
