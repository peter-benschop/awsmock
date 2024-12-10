//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/EventRecord.h>

namespace AwsMock::Dto::SQS {

    std::string Record::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Record::ToDocument() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "awsRegion", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "messageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "receiptHandle", receiptHandle);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "body", body);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "md5OfBody", md5Sum);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "eventSource", eventSource);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "eventSourceARN", eventSourceArn);

            if (!messagesAttributes.empty()) {
                array jsonMessageAttributeArray;
                for (const auto &[fst, snd]: messagesAttributes) {
                    document jsonAttribute;
                    jsonAttribute.append(kvp(fst, snd.ToDocument()));
                    jsonMessageAttributeArray.append(jsonAttribute);
                }
                rootDocument.append(kvp("messageAttributes", jsonMessageAttributeArray));
            }

            if (!attributes.empty()) {
                document jsonAttributeObject;
                for (const auto &[fst, snd]: attributes) {
                    jsonAttributeObject.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("attributes", jsonAttributeObject));
            }
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Record::FromJson(const view_or_value<view, value> &object) {

        try {

            region = Core::Bson::BsonUtils::GetStringValue(object, "awsRegion");
            messageId = Core::Bson::BsonUtils::GetStringValue(object, "messageId");
            receiptHandle = Core::Bson::BsonUtils::GetStringValue(object, "receiptHandle");
            body = Core::Bson::BsonUtils::GetStringValue(object, "body");
            md5Sum = Core::Bson::BsonUtils::GetStringValue(object, "md5OfBody");
            eventSource = Core::Bson::BsonUtils::GetStringValue(object, "eventSource");
            eventSourceArn = Core::Bson::BsonUtils::GetStringValue(object, "eventSourceArn");

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string Record::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Record &r) {
        os << "Record=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
