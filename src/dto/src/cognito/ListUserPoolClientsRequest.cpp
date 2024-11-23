//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolClientsRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListUserPoolClientsRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolClientsRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("MaxResults", maxResults);
            rootJson.set("NextToken", nextToken);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUserPoolClientsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUserPoolClientsRequest &r) {
        os << "ListUserPoolClientsRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito