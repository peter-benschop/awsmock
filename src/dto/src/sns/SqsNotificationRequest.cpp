//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/SqsNotificationRequest.h>

namespace AwsMock::Dto::SNS {

    std::string SqsNotificationRequest::ToJson() const {


        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Type", type);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TopicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Message", message);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "Timestamp", timestamp);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "SignatureVersion", signatureVersion);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Signature", signature);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "SignatureCertURL", signingCertURL);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "UnsubscribeURL", unsubscribeURL);

            document messageAttributesDocument;
            MessageAttributeList messageAttributeListDto;
            for (const auto &[fst, snd]: messageAttributes) {

                MessageAttribute messageAttributeDto = {.name = snd.name, .stringValue = snd.stringValue};

                if (snd.type == STRING) {
                    Core::Bson::BsonUtils::SetStringValue(messageAttributesDocument, "DataType", "String");
                    Core::Bson::BsonUtils::SetStringValue(messageAttributesDocument, "StringValue", snd.stringValue);
                    messageAttributeDto.type = STRING;
                } else if (snd.type == NUMBER) {
                    Core::Bson::BsonUtils::SetStringValue(messageAttributesDocument, "DataType", "Number");
                    Core::Bson::BsonUtils::SetStringValue(messageAttributesDocument, "StringValue", snd.stringValue);
                    messageAttributeDto.type = NUMBER;
                }
                messageAttributeListDto[snd.name] = messageAttributeDto;
                messageAttributesDocument.append(kvp(snd.name, messageAttributesDocument.extract()));
            }
            messageAttributesDocument.append(kvp("MessageAttributes", messageAttributesDocument.extract()));

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SqsNotificationRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SqsNotificationRequest &r) {
        os << "SqsNotificationRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
