//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/Bucket.h>

namespace AwsMock::Dto::S3 {

    void Bucket::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("bucketName", jsonObject, bucketName);
        Core::JsonUtils::GetJsonValueString("owner", jsonObject, owner);
        Core::JsonUtils::GetJsonValueLong("size", jsonObject, size);
        Core::JsonUtils::GetJsonValueLong("keys", jsonObject, keys);
        Core::JsonUtils::GetJsonValueString("versionStatus", jsonObject, versionStatus);

        if (jsonObject->has("queueConfigurations")) {
            Poco::JSON::Array::Ptr jsonQueueConfigurationArray = jsonObject->getArray("queueConfigurations");
            for (int i = 0; i < jsonQueueConfigurationArray->size(); i++) {
                Dto::S3::QueueConfiguration queueConfiguration;
                queueConfiguration.FromJsonObject(jsonQueueConfigurationArray->getObject(i));
                queueConfigurations.emplace_back(queueConfiguration);
            }
        }
    }

    std::string Bucket::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    Poco::JSON::Object Bucket::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("name", bucketName);
            rootJson.set("owner", owner);
            rootJson.set("size", size);
            rootJson.set("keys", keys);
            rootJson.set("versionStatus", versionStatus);

            if (!queueConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &queueNotification: queueConfigurations) {
                    jsonArray.add(queueNotification.ToJsonObject());
                }
                rootJson.set("queueConfigurations", jsonArray);
            }

            if (!topicConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &topicNotification: topicConfigurations) {
                    jsonArray.add(topicNotification.ToJsonObject());
                }
                rootJson.set("topicConfigurations", jsonArray);
            }

            if (!lambdaConfigurations.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &lambdaNotification: lambdaConfigurations) {
                    jsonArray.add(lambdaNotification.ToJsonObject());
                }
                rootJson.set("lambdaConfigurations", jsonArray);
            }
            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Bucket::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Bucket &c) {
        os << "Bucket=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
