//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/model/Message.h>

namespace AwsMock::Dto::SNS {

    std::string Message::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    view_or_value<view, value> Message::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "TopicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(document, "Message", message);
            Core::Bson::BsonUtils::SetDateValue(document, "Created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "Modified", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Message::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &r) {
        os << "Message=" + r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
