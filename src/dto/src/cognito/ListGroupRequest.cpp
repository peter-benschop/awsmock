//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListGroupsRequest.h>

namespace AwsMock::Dto::Cognito {

    void ListGroupsRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);
            Core::JsonUtils::GetJsonValueInt("Limit", rootObject, limit);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListGroupsRequest::ToJson() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("NextToken", nextToken);
            rootJson.set("Limit", limit);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListGroupsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListGroupsRequest &r) {
        os << "ListGroupsRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito