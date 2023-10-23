//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/UserIdentity.h>

namespace AwsMock::Dto::S3 {

  Poco::JSON::Object UserIdentity::ToJsonObject() const {
    try {
      Poco::JSON::Object rootJson;
      rootJson.set("principalId", principalId);
      return rootJson;
    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string UserIdentity::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UserIdentity &r) {
    os << "UserIdentity={principalId='" + r.principalId + "'}";
    return os;
  }
}
