//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

  std::string ListUserPoolResponse::ToJson() const {

    try {
      Poco::JSON::Object rootObject;

      Poco::JSON::Array userPoolArray;
      for (const auto &userPool : userPools) {
        Poco::JSON::Object userPoolJson;
        userPoolJson.set("Id", userPool.userPoolId);
        userPoolJson.set("Name", userPool.name);
        userPoolJson.set("LastModifiedDate", std::to_string(userPool.modified.timestamp().epochTime()));
        userPoolJson.set("CreationDate", std::to_string(userPool.modified.timestamp().epochTime()));
        userPoolArray.add(userPoolJson);
      }

      rootObject.set("UserPools", userPoolArray);
      std::ostringstream os;
      rootObject.stringify(os);
      std::string tmp = os.str();
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
    os << "ListUserPoolResponse=" << r.ToJson();
    return os;
  }
}