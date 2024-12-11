//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolClientsResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListUserPoolClientsResponse::ToJson() const {

        try {

            document rootDocument;

            if (!userPoolsClients.empty()) {
                array userPoolClientArray;
                for (const auto &userPoolClient: userPoolsClients) {
                    userPoolClientArray.append(userPoolClient.ToDocument());
                }
                rootDocument.append(kvp("UserPoolClients", userPoolClientArray));
            }
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "NextToken", nextToken);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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