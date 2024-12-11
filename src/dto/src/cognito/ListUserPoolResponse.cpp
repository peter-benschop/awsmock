//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "Total", total);

            if (!userPools.empty()) {
                array userPoolArray;
                for (const auto &userPool: userPools) {
                    document userPoolJson;
                    userPoolJson.append(kvp("Id", userPool.userPoolId));
                    userPoolJson.append(kvp("Name", userPool.name));
                    userPoolJson.append(kvp("Region", userPool.region));
                    userPoolJson.append(kvp("LastModifiedDate", std::chrono::duration_cast<std::chrono::seconds>(userPool.modified.time_since_epoch()).count()));
                    userPoolJson.append(kvp("CreationDate", std::chrono::duration_cast<std::chrono::seconds>(userPool.created.time_since_epoch()).count()));
                    userPoolArray.append(userPoolJson);
                }
                rootDocument.append(kvp("UserPools", userPoolArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListUserPoolResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolResponse &r) {
        os << "ListUserPoolResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito