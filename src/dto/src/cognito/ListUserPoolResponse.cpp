//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            Poco::JSON::Array userPoolArray;
            for (const auto &userPool: userPools) {
                Poco::JSON::Object userPoolJson;
                userPoolJson.set("Id", userPool.userPoolId);
                userPoolJson.set("Name", userPool.name);
                userPoolJson.set("Region", userPool.region);
                userPoolJson.set("LastModifiedDate", std::chrono::duration_cast<std::chrono::seconds>(userPool.modified.time_since_epoch()).count());
                userPoolJson.set("CreationDate", std::chrono::duration_cast<std::chrono::seconds>(userPool.created.time_since_epoch()).count());
                userPoolArray.add(userPoolJson);
            }
            rootObject.set("UserPools", userPoolArray);
            rootObject.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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
}// namespace AwsMock::Dto::Cognito