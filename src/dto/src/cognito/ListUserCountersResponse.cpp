//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserCountersResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserCountersResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;

            if (!users.empty()) {
                Poco::JSON::Array userArray;
                for (const auto &user: users) {
                    Poco::JSON::Object userJson;
                    userJson.set("id", user.oid);
                    userJson.set("userPoolId", user.userPoolId);
                    userJson.set("userName", user.userName);
                    userJson.set("region", user.region);
                    userJson.set("status", UserStatusToString(user.userStatus));
                    userJson.set("enabled", user.enabled);
                    userJson.set("created", Core::DateTimeUtils::ToISO8601(user.created));
                    userJson.set("modified", Core::DateTimeUtils::ToISO8601(user.modified));
                    userArray.add(userJson);
                }
                rootObject.set("users", userArray);
            }
            rootObject.set("total", total);
            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserCountersResponse &r) {
        os << "ListUserCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito