//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolClientsResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolClientsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            Poco::JSON::Array userPoolClientArray;
            for (const auto &userPoolClient: userPoolsClients) {
                Poco::JSON::Object userPoolJson = userPoolClient.ToJsonObject();
                userPoolClientArray.add(userPoolJson);
            }
            rootObject.set("UserPoolClients", userPoolClientArray);
            rootObject.set("NextToken", nextToken);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolClientsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolClientsResponse &r) {
        os << "ListUserPoolClientsResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito