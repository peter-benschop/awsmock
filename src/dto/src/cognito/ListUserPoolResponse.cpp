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
                userPoolJson.set("LastModifiedDate", std::to_string(userPool.lastModified.timestamp().epochTime()));
                userPoolJson.set("CreationDate", std::to_string(userPool.created.timestamp().epochTime()));
                userPoolArray.add(userPoolJson);
            }
            rootObject.set("UserPools", userPoolArray);

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