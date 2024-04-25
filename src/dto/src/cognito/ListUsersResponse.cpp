//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUsersResponse::ToJson() const {

        try {
            Poco::JSON::Object rootObject;

            Poco::JSON::Array usersArray;
            for (const auto &user: users) {
                Poco::JSON::Object userJson;
                userJson.set("Username", user.userName);
                userJson.set("Enabled", user.enabled);
                userJson.set("UserStatus", Database::Entity::Cognito::UserStatusToString(user.userStatus));
                userJson.set("LastModifiedDate", std::to_string(user.modified.timestamp().epochTime()));
                userJson.set("CreationDate", std::to_string(user.modified.timestamp().epochTime()));
                usersArray.add(userJson);
            }
            rootObject.set("Users", usersArray);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUsersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersResponse &r) {
        os << "ListUsersResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito