//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/MessageFailed.h>

namespace AwsMock::Dto::SQS {

    std::string MessageFailed::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> MessageFailed::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Code", code);
            Core::Bson::BsonUtils::SetStringValue(document, "Message", message);
            Core::Bson::BsonUtils::SetBoolValue(document, "SenderFault", senderFault);

            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void MessageFailed::FromDocument(const view_or_value<view, value> &document) {

        try {

            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            code = Core::Bson::BsonUtils::GetStringValue(document, "code");
            message = Core::Bson::BsonUtils::GetStringValue(document, "message");
            senderFault = Core::Bson::BsonUtils::GetBoolValue(document, "senderFault");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string MessageFailed::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageFailed &r) {
        os << "MessageFailed=" << r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
