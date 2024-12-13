//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolCountersResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolCountersResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetLongValue(document, "total", total);

            if (!userPools.empty()) {
                array jsonArray;
                for (const auto &userPool: userPools) {
                    jsonArray.append(userPool.ToDocument());
                }
                document.append(kvp("userPools", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListUserPoolCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolCountersResponse &r) {
        os << "ListUserPoolCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito