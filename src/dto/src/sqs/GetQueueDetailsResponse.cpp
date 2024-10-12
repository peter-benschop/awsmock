//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/sqs/GetQueueDetailsResponse.h>

namespace AwsMock::Dto::SQS {

    std::string GetQueueDetailsResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("queueName", queueName);
            rootJson.set("queueUrl", queueUrl);
            rootJson.set("queueArn", queueArn);
            rootJson.set("messageCount", messageCount);
            rootJson.set("retentionPeriod", retentionPeriod);
            rootJson.set("size", size);
            rootJson.set("delay", delay);
            rootJson.set("maxMessageSize", maxMessageSize);
            rootJson.set("visibilityTimeout", visibilityTimeout);
            rootJson.set("owner", owner);
            rootJson.set("available", available);
            rootJson.set("invisible", invisible);
            rootJson.set("delayed", delayed);
            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetQueueDetailsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueDetailsResponse &r) {
        os << "GetQueueDetailsResponse=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
