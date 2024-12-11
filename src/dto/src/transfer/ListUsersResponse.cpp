//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListUsersResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string ListUsersResponse::ToJson() const {

        // Todo:
        /*
        try {

            Poco::JSON::Array usersJsonArray;
            for (const auto &user: users) {
                usersJsonArray.add(user.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ServerId", serverId);
            //rootJson.set("NextToken", nextToken);
            rootJson.set("Users", usersJsonArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string ListUsersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersResponse &r) {
        os << "ListUserResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
