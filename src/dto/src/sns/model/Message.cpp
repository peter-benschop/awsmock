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
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TopicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Message", message);
            Core::Bson::BsonUtils::SetDateValue(rootDocument, "Created", created);
            Core::Bson::BsonUtils::SetDateValue(rootDocument, "Modified", modified);

            if (!messageAttributes.empty()) {
                array jsonMessageAttributeArray;
                for (const auto &[fst, snd]: messageAttributes) {
                    document jsonAttribute;
                    jsonAttribute.append(kvp(fst, snd.ToDocument()));
                    jsonMessageAttributeArray.append(jsonAttribute);
                }
                rootDocument.append(kvp("MessageAttributes", jsonMessageAttributeArray));
            }

            return rootDocument.extract();

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
