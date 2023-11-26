//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

  std::string ListUserPoolResponse::ToJson() {

    try {
      Poco::JSON::Object rootObject;

      Poco::JSON::Array userPoolArray;
      for (const auto &userPool : userPools) {
        Poco::JSON::Object userPoolJson;
        userPoolJson.set("Id", userPool.id);
        userPoolJson.set("Name", userPool.name);
        userPoolJson.set("LastModifiedDate", Poco::DateTimeFormatter().format(userPool.modified, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
        userPoolJson.set("CreationDate", Poco::DateTimeFormatter().format(userPool.created, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
        userPoolArray.add(userPoolJson);
      }

      rootObject.set("UserPools", userPoolArray);
      std::ostringstream os;
      rootObject.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListUserPoolResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListUserPoolResponse &r) {
    os << "ListUserPoolResponse={userPools={";
    for (const auto &userPool : r.userPools) {
      os << userPool.ToString() << ", ";
    }
    os << "\b\b" << "}";
    return os;
  }
}