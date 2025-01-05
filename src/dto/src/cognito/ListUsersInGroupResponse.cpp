//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersInGroupResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUsersInGroupResponse::ToJson() const {

        try {

            document rootDocument;

            if (!users.empty()) {
                array jsonArray;
                for (const auto &user: users) {
                    jsonArray.append(user.ToDocument());
                }
                rootDocument.append(kvp("Users", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListUsersInGroupResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersInGroupResponse &r) {
        os << "ListUsersInGroupResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito