//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetBucketResponse.h>

namespace AwsMock::Dto::S3 {

    std::string GetBucketResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("id", id);
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("arn", arn);
            rootJson.set("size", size);
            rootJson.set("keys", keys);
            rootJson.set("versionStatus", versionStatus);

            if (!lambdaConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &lambdaNotification: lambdaConfigurations) {
                    jsonArray.add(lambdaNotification.ToJsonObject());
                }
                rootJson.set("lambdaConfigurations", jsonArray);
            }

            if (!queueConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &topicConfiguration: queueConfigurations) {
                    jsonArray.add(topicConfiguration.ToJsonObject());
                }
                rootJson.set("queueConfigurations", jsonArray);
            }

            if (!topicConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &topicConfiguration: topicConfigurations) {
                    jsonArray.add(topicConfiguration.ToJsonObject());
                }
                rootJson.set("topicConfigurations", jsonArray);
            }

            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetBucketResponse &r) {
        os << "GetBucketResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
