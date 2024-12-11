//
// Created by vogje01 on 12/10/23.
//

#include <awsmock/entity/sqs/QueueAttribute.h>

namespace AwsMock::Database::Entity::SQS {

    view_or_value<view, value> QueueAttribute::ToDocument() const {

        view_or_value<view, value> queueAttributetDoc = make_document(
                kvp("delaySeconds", delaySeconds),
                kvp("maxMessageSize", maxMessageSize),
                kvp("messageRetentionPeriod", messageRetentionPeriod),
                kvp("policy", policy),
                kvp("receiveMessageWaitTime", receiveMessageWaitTime),
                kvp("visibilityTimeout", visibilityTimeout),
                kvp("redrivePolicy", redrivePolicy.ToDocument()),
                kvp("redriveAllowPolicy", redriveAllowPolicy),
                kvp("approximateNumberOfMessages", static_cast<bsoncxx::types::b_int64>(approximateNumberOfMessages)),
                kvp("approximateNumberOfMessagesDelayed", static_cast<bsoncxx::types::b_int64>(approximateNumberOfMessagesDelayed)),
                kvp("approximateNumberOfMessagesNotVisible", static_cast<bsoncxx::types::b_int64>(approximateNumberOfMessagesNotVisible)),
                kvp("queueArn", queueArn));

        return queueAttributetDoc;
    }

    void QueueAttribute::FromDocument(std::optional<bsoncxx::document::view> mResult) {

        try {

            delaySeconds = Core::Bson::BsonUtils::GetIntValue(mResult, "delaySeconds");
            maxMessageSize = Core::Bson::BsonUtils::GetIntValue(mResult, "maxMessageSize");
            messageRetentionPeriod = Core::Bson::BsonUtils::GetIntValue(mResult, "messageRetentionPeriod");
            policy = Core::Bson::BsonUtils::GetStringValue(mResult, "policy");
            receiveMessageWaitTime = Core::Bson::BsonUtils::GetIntValue(mResult, "receiveMessageWaitTime");
            visibilityTimeout = Core::Bson::BsonUtils::GetIntValue(mResult, "visibilityTimeout");
            redrivePolicy.FromDocument(mResult.value()["redrivePolicy"].get_document().value);
            redriveAllowPolicy = Core::Bson::BsonUtils::GetStringValue(mResult, "redriveAllowPolicy");
            approximateNumberOfMessages = Core::Bson::BsonUtils::GetLongValue(mResult, "approximateNumberOfMessages");
            approximateNumberOfMessagesDelayed = Core::Bson::BsonUtils::GetLongValue(mResult, "approximateNumberOfMessagesDelayed");
            approximateNumberOfMessagesNotVisible = Core::Bson::BsonUtils::GetLongValue(mResult, "approximateNumberOfMessagesNotVisible");

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string QueueAttribute::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueAttribute &r) {
        os << "QueueAttribute=" << to_json(r.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS
