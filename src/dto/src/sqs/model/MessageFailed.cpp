//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/MessageFailed.h>

namespace AwsMock::Dto::SQS {

    std::string MessageFailed::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object MessageFailed::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("Code", code);
            rootJson.set("Message", message);
            rootJson.set("SenderFault", senderFault);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void MessageFailed::FromJson(const Poco::JSON::Object::Ptr &object) {

        try {

            Core::JsonUtils::GetJsonValueString("Id", object, id);
            Core::JsonUtils::GetJsonValueString("Code", object, code);
            Core::JsonUtils::GetJsonValueString("Message", object, message);
            Core::JsonUtils::GetJsonValueBool("SenderFault", object, senderFault);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string MessageFailed::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageFailed &r) {
        os << "MessageFailed=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
