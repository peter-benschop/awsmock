//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/sns/GetTopicDetailsResponse.h>

namespace AwsMock::Dto::SNS {

    std::string GetTopicDetailsResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("topicName", topicName);
            rootJson.set("topicUrl", topicUrl);
            rootJson.set("topicArn", topicArn);
            rootJson.set("messageCount", messageCount);
            rootJson.set("size", size);
            rootJson.set("owner", owner);
            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetTopicDetailsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetTopicDetailsResponse &r) {
        os << "GetTopicDetailsResponse=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
