//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/sqs/model/QueueCounter.h>

namespace AwsMock::Dto::SQS {

    std::string QueueCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> QueueCounter::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "queueName", queueName);
            Core::Bson::BsonUtils::SetStringValue(document, "queueArn", queueArn);
            Core::Bson::BsonUtils::SetStringValue(document, "queueUrl", queueUrl);
            Core::Bson::BsonUtils::SetLongValue(document, "available", available);
            Core::Bson::BsonUtils::SetLongValue(document, "invisible", invisible);
            Core::Bson::BsonUtils::SetLongValue(document, "delayed", delayed);
            Core::Bson::BsonUtils::SetIntValue(document, "visibilityTimeout", visibilityTimeout);
            Core::Bson::BsonUtils::SetIntValue(document, "delay", delay);
            Core::Bson::BsonUtils::SetLongValue(document, "retentionPeriod", retentionPeriod);
            Core::Bson::BsonUtils::SetLongValue(document, "maxMessageSize", maxMessageSize);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            Core::Bson::BsonUtils::SetBoolValue(document, "isDlq", isDlq);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string QueueCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueCounter &r) {
        os << "QueueCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SQS
