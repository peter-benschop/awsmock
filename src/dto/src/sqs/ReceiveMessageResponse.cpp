//
// Created by vogje01 on 03/10/2023.
//

#include "awsmock/core/XmlUtils.h"
#include <awsmock/dto/sqs/ReceiveMessageResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ReceiveMessageResponse::ToJson() {

        try {
            Poco::JSON::Object rootJson;

            Poco::JSON::Array messageArray;
            for (const auto &message: messageList) {

                Poco::JSON::Object messageObject;
                messageObject.set("Body", message.body);
                messageObject.set("ReceiptHandle", message.receiptHandle);
                messageObject.set("MD5OfBody", message.md5Body);
                messageObject.set("MessageId", message.messageId);

                Dto::SQS::MessageAttributeList messageAttributeListDto;

                // Message attributes
                Poco::JSON::Object messageAttributeObject;
                for (const auto &at: message.messageAttributes) {

                    Dto::SQS::MessageAttribute messageAttributeDto = {.name = at.attributeName, .stringValue = at.attributeValue};

                    Poco::JSON::Object messageAttributesObject;
                    if (at.attributeType == Database::Entity::SQS::MessageAttributeType::STRING) {
                        messageAttributesObject.set("DataType", "String");
                        messageAttributesObject.set("StringValue", at.attributeValue);
                        messageAttributeDto.type = MessageAttributeDataType::STRING;
                    } else if (at.attributeType == Database::Entity::SQS::MessageAttributeType::NUMBER) {
                        messageAttributesObject.set("DataType", "Number");
                        messageAttributesObject.set("StringValue", at.attributeValue);
                        messageAttributeDto.type = MessageAttributeDataType::NUMBER;
                    }
                    messageAttributeListDto[at.attributeName] = messageAttributeDto;
                    messageAttributeObject.set(at.attributeName, messageAttributesObject);
                }
                messageObject.set("MessageAttributes", messageAttributeObject);

                // Attributes
                Poco::JSON::Object attributeObject;
                for (const auto &at: message.attributes) {
                    attributeObject.set(at.first, at.second);
                }
                messageObject.set("Attributes", attributeObject);

                // MD5 of message attributes
                messageObject.set("MD5OfMessageAttributes", Dto::SQS::MessageAttribute::GetMd5MessageAttributes(messageAttributeListDto));
                messageArray.add(messageObject);
            }

            // Add message array
            rootJson.set("Messages", messageArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ReceiveMessageResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "ReceiveMessageResponse");

        // ReceiveMessageResult
        Poco::XML::AutoPtr<Poco::XML::Element> pResult = Core::XmlUtils::CreateNode(pDoc, pRoot, "ReceiveMessageResult");

        for (auto &it: messageList) {

            // Message
            Poco::XML::AutoPtr<Poco::XML::Element> pMessage = Core::XmlUtils::CreateNode(pDoc, pResult, "Message");

            // MessageId
            Core::XmlUtils::CreateTextNode(pDoc, pMessage, "MessageId", it.messageId);
            Core::XmlUtils::CreateTextNode(pDoc, pMessage, "ReceiptHandle", it.receiptHandle);
            Core::XmlUtils::CreateTextNode(pDoc, pMessage, "Body", it.body);
            Core::XmlUtils::CreateTextNode(pDoc, pMessage, "MD5OfBody", it.md5Body);
            Core::XmlUtils::CreateTextNode(pDoc, pMessage, "MD5OfMessageAttributes", it.md5UserAttr);

            // MessageAttribute
            Poco::XML::AutoPtr<Poco::XML::Element> pAttribute = Core::XmlUtils::CreateNode(pDoc, pMessage, "Attributes");

            for (const auto &at: it.attributes) {

                // Nodes
                Core::XmlUtils::CreateTextNode(pDoc, pAttribute, "Name", at.first);
                Core::XmlUtils::CreateTextNode(pDoc, pAttribute, "Value", at.second);
            }

            // Message attributes
            Poco::XML::AutoPtr<Poco::XML::Element> pMessageAttributes = Core::XmlUtils::CreateNode(pDoc, pMessage, "MessageAttributes");

            for (const auto &at: it.messageAttributes) {

                // MessageAttribute
                Poco::XML::AutoPtr<Poco::XML::Element> pMessageAttribute = Core::XmlUtils::CreateNode(pDoc, pMessageAttributes, at.attributeName);
                Core::XmlUtils::CreateTextNode(pDoc, pMessageAttribute, "DataType", at.attributeType);
                Core::XmlUtils::CreateTextNode(pDoc, pMessageAttribute, "StringValue", at.attributeValue);
            }
        }

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = Core::XmlUtils::CreateNode(pDoc, pRoot, "ResponseMetadata");
        Core::XmlUtils::CreateTextNode(pDoc, pMetaData, "RequestId", requestId);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string ReceiveMessageResponse::ToString() {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, ReceiveMessageResponse &r) {
        os << "ReceiveMessageResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
