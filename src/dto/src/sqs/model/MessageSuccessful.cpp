//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/MessageSuccessful.h>

namespace AwsMock::Dto::SQS {

    std::string MessageSuccessful::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object MessageSuccessful::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("MessageId", messageId);
            rootJson.set("SequenceNumber", sequenceNumber);
            rootJson.set("MD5OfMessageBody", md5Body);
            rootJson.set("MD5OfMessageAttributes", md5UserAttr);
            rootJson.set("MD5OfMessageSystemAttributes", md5SystemAttr);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void MessageSuccessful::FromJson(const Poco::JSON::Object::Ptr &object) {

        try {

            Core::JsonUtils::GetJsonValueString("Id", object, id);
            Core::JsonUtils::GetJsonValueString("MessageId", object, messageId);
            Core::JsonUtils::GetJsonValueString("SequenceNumber", object, sequenceNumber);
            Core::JsonUtils::GetJsonValueString("MD5OfMessageBody", object, md5Body);
            Core::JsonUtils::GetJsonValueString("MD5OfMessageAttributes", object, md5UserAttr);
            Core::JsonUtils::GetJsonValueString("MD5OfMessageSystemAttributes", object, md5SystemAttr);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string MessageSuccessful::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageSuccessful &r) {
        os << "MessageSuccessful=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
