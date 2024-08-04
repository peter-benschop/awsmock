//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersInGroupResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUsersInGroupResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            Poco::JSON::Array userArray;
            for (const auto &user: users) {
                Poco::JSON::Object userJson = user.ToJsonObject();
                userArray.add(userJson);
            }
            rootObject.set("Users", userArray);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUsersInGroupResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersInGroupResponse &r) {
        os << "ListUsersInGroupResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito