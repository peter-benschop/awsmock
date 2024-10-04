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

    void QueueAttribute::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        delaySeconds = mResult.value()["delaySeconds"].get_int32().value;
        maxMessageSize = mResult.value()["maxMessageSize"].get_int32().value;
        messageRetentionPeriod = mResult.value()["messageRetentionPeriod"].get_int32().value;
        policy = bsoncxx::string::to_string(mResult.value()["policy"].get_string().value);
        receiveMessageWaitTime = mResult.value()["receiveMessageWaitTime"].get_int32().value;
        visibilityTimeout = mResult.value()["visibilityTimeout"].get_int32().value;
        redrivePolicy.FromDocument(mResult.value()["redrivePolicy"].get_document().value);
        redriveAllowPolicy = bsoncxx::string::to_string(mResult.value()["redriveAllowPolicy"].get_string().value);
        approximateNumberOfMessages = static_cast<long>(mResult.value()["approximateNumberOfMessages"].get_int64().value);
        approximateNumberOfMessagesDelayed = static_cast<long>(mResult.value()["approximateNumberOfMessagesDelayed"].get_int64().value);
        approximateNumberOfMessagesNotVisible = static_cast<long>(mResult.value()["approximateNumberOfMessagesNotVisible"].get_int64().value);
    }

    Poco::JSON::Object QueueAttribute::ToJsonObject() const {

        using Core::JsonUtils;

        try {

            Poco::JSON::Object jsonObject;
            JsonUtils::SetJsonValueInt(jsonObject, "delaySeconds", delaySeconds);
            JsonUtils::SetJsonValueInt(jsonObject, "maxMessageSize", maxMessageSize);
            JsonUtils::SetJsonValueInt(jsonObject, "messageRetentionPeriod", messageRetentionPeriod);
            JsonUtils::SetJsonValueString(jsonObject, "policy", policy);
            JsonUtils::SetJsonValueInt(jsonObject, "receiveMessageWaitTime", receiveMessageWaitTime);
            JsonUtils::SetJsonValueInt(jsonObject, "visibilityTimeout", visibilityTimeout);
            JsonUtils::SetJsonValueString(jsonObject, "redriveAllowPolicy", redriveAllowPolicy);
            JsonUtils::SetJsonValueInt(jsonObject, "approximateNumberOfMessages", approximateNumberOfMessages);
            JsonUtils::SetJsonValueInt(jsonObject, "approximateNumberOfMessagesDelayed", approximateNumberOfMessagesDelayed);
            JsonUtils::SetJsonValueInt(jsonObject, "approximateNumberOfMessagesNotVisible", approximateNumberOfMessagesNotVisible);
            jsonObject.set("redrivePolicy", redrivePolicy.ToJsonObject());

            return jsonObject;

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void QueueAttribute::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueInt("delaySeconds", jsonObject, delaySeconds);
            Core::JsonUtils::GetJsonValueInt("maxMessageSize", jsonObject, maxMessageSize);
            Core::JsonUtils::GetJsonValueInt("messageRetentionPeriod", jsonObject, messageRetentionPeriod);
            Core::JsonUtils::GetJsonValueString("policy", jsonObject, policy);
            Core::JsonUtils::GetJsonValueInt("receiveMessageWaitTime", jsonObject, receiveMessageWaitTime);
            Core::JsonUtils::GetJsonValueInt("visibilityTimeout", jsonObject, visibilityTimeout);
            Core::JsonUtils::GetJsonValueString("redriveAllowPolicy", jsonObject, redriveAllowPolicy);
            Core::JsonUtils::GetJsonValueLong("approximateNumberOfMessages", jsonObject, approximateNumberOfMessages);
            Core::JsonUtils::GetJsonValueLong("approximateNumberOfMessagesDelayed", jsonObject, approximateNumberOfMessagesDelayed);
            Core::JsonUtils::GetJsonValueLong("approximateNumberOfMessagesNotVisible", jsonObject, approximateNumberOfMessagesNotVisible);
            redrivePolicy.FromJsonObject(jsonObject->getObject("redrivePolicy"));

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string QueueAttribute::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueAttribute &r) {
        os << "QueueAttribute=" << bsoncxx::to_json(r.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS
