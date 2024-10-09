//
// Created by vogje01 on 10/9/24.
//

#include <awsmock/dto/sns/ListMessagesRequest.h>

namespace AwsMock::Dto::SNS {

    std::string ListMessagesRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("topicArn", topicArn);
            rootJson.set("pageSize", pageSize);
            rootJson.set("pageIndex", pageIndex);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListMessagesRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            std::string tmpStr;
            Core::JsonUtils::GetJsonValueString("region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("topicArn", rootObject, topicArn);
            Core::JsonUtils::GetJsonValueInt("pageSize", rootObject, pageSize);
            Core::JsonUtils::GetJsonValueInt("pageIndex", rootObject, pageIndex);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListMessagesRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessagesRequest &r) {
        os << "ListMessagesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
