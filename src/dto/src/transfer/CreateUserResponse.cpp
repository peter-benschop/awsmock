//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/CreateUserResponse.h>

namespace AwsMock::Dto::Transfer {

  std::string CreateUserResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("ServerId", serverId);
      rootJson.set("UserName", userName);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateUserResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateUserResponse &r) {
    os << "CreateUserResponse={region='" << r.region << "' serverId='" << r.serverId << "' userName='" << r.userName << "'}";
    return os;
  }

} // namespace AwsMock::Dto::Transfer
