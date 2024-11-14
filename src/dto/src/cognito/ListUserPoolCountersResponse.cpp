//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolCountersResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolCountersResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;

            if (!userPools.empty()) {
                Poco::JSON::Array userPoolArray;
                for (const auto &userPool: userPools) {
                    Poco::JSON::Object userPoolJson;
                    userPoolJson.set("id", userPool.id);
                    userPoolJson.set("userPoolId", userPool.userPoolId);
                    userPoolJson.set("name", userPool.name);
                    userPoolJson.set("region", userPool.region);
                    userPoolJson.set("userCount", userPool.userCount);
                    userPoolJson.set("created", Core::DateTimeUtils::ToISO8601(userPool.created));
                    userPoolJson.set("modified", Core::DateTimeUtils::ToISO8601(userPool.modified));
                    userPoolArray.add(userPoolJson);
                }
                rootObject.set("userPools", userPoolArray);
            }
            rootObject.set("total", total);
            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolCountersResponse &r) {
        os << "ListUserPoolCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito