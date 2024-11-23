//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListUsersRequest.h>

namespace AwsMock::Dto::Transfer {

    std::string ListUsersRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ServerId", serverId);
            rootJson.set("MaxResults", maxResults);
            rootJson.set("NextToken", nextToken);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListUsersRequest::FromJson(const std::string &body) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Get root values
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);
            Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListUsersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListUsersRequest &r) {
        os << "ListUsersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
