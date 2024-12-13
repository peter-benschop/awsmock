//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserCountersResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserCountersResponse::ToJson() const {

        try {

            document document;
            if (!users.empty()) {
                array jsonArray;
                for (const auto &user: users) {
                    jsonArray.append(user.ToDocument());
                }
                document.append(kvp("users", users));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListUserCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserCountersResponse &r) {
        os << "ListUserCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito