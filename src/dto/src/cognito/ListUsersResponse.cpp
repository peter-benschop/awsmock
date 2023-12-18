//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersResponse.h>

namespace AwsMock::Dto::Cognito {

  std::string ListUsersResponse::ToJson() {

    try {
      Poco::JSON::Object rootObject;

      Poco::JSON::Array usersArray;
      for (const auto &user : users) {
        Poco::JSON::Object userJson;
        userJson.set("Username", user.userName);
        userJson.set("Enabled", user.enabled);
        userJson.set("UserStatus", Database::Entity::Cognito::UserStatusToString(user.userStatus));
        userJson.set("LastModifiedDate", std::to_string(user.modified.timestamp().epochTime()));
        userJson.set("CreationDate", std::to_string(user.modified.timestamp().epochTime()));
        usersArray.add(userJson);
      }

      rootObject.set("Users", usersArray);
      std::ostringstream os;
      rootObject.stringify(os);
      std::string tmp = os.str();
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListUsersResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListUsersResponse &r) {
    os << "ListUsersResponse={users={";
    for (const auto &user : r.users) {
      os << user.ToString() << ", ";
    }
    os << "\b\b" << "}";
    return os;
  }
}