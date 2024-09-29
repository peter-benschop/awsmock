//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueCountersRequest.h>

namespace AwsMock::Dto::SQS {

    void ListQueueCountersRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Values
            Core::JsonUtils::GetJsonValueInt("pageSize", rootObject, pageSize);
            Core::JsonUtils::GetJsonValueInt("pageIndex", rootObject, pageIndex);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListQueueCountersRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("pageSize", pageSize);
            rootJson.set("pageIndex", pageIndex);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListQueueCountersRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueueCountersRequest &r) {
        os << "ListQueueCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
