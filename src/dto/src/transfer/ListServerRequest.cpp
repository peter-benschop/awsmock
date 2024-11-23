//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerRequest.h>

namespace AwsMock::Dto::Transfer {

    std::string ListServerRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("MaxResults", maxResults);
            rootJson.set("NextToken", nextToken);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListServerRequest::FromJson(const std::string &body) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Get root values
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListServerRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListServerRequest &r) {
        os << "ListServerRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
