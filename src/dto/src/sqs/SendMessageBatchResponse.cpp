//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageBatchResponse.h>

namespace AwsMock::Dto::SQS {

    std::string SendMessageBatchResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            if (!failed.empty()) {
                Poco::JSON::Array jsonFailedArray;
                for (const auto &fail: failed) {
                    jsonFailedArray.add(fail.ToJsonObject());
                }
                rootJson.set("Failed", jsonFailedArray);
            }

            if (!successful.empty()) {
                Poco::JSON::Array jsonSuccessfulArray;
                for (const auto &s: successful) {
                    jsonSuccessfulArray.add(s.ToJsonObject());
                }
                rootJson.set("Successful", jsonSuccessfulArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void SendMessageBatchResponse::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

            const auto &failedArray = rootObject->getArray("Failed");
            for (int i = 0; i < failedArray->size(); i++) {
                MessageFailed failedMessage;
                failedMessage.FromJson(failedArray->getObject(i));
                failed.emplace_back(failedMessage);
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void SendMessageBatchResponse::FromXml(const std::string &xmlString) {

        /*Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/SendMessageResponse/SendMessageResult/MessageId");
        if (node) {
            messageId = node->innerText();
        } else {
            std::cerr << "Exception: Wrong send message payload" << std::endl;
        }
        node = pDoc->getNodeByPath("/SendMessageResponse/SendMessageResult/MD5OfMessageBody");
        if (node) {
            md5Body = node->innerText();
        } else {
            std::cerr << "Exception: Wrong send message payload" << std::endl;
        }
        node = pDoc->getNodeByPath("/SendMessageResponse/SendMessageResult/MD5OfMessageAttributes");
        if (node) {
            md5UserAttr = node->innerText();
        } else {
            std::cerr << "Exception: Wrong send message payload" << std::endl;
        }*/
    }

    std::string SendMessageBatchResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("SendMessageBatchResponse");
        pDoc->appendChild(pRoot);

        /*// SendMessageResult
        Poco::XML::AutoPtr<Poco::XML::Element> pSendMessageResult = pDoc->createElement("SendMessageResult");
        pRoot->appendChild(pSendMessageResult);

        // MessageID
        Poco::XML::AutoPtr<Poco::XML::Element> pMessageId = pDoc->createElement("MessageId");
        pSendMessageResult->appendChild(pMessageId);
        Poco::XML::AutoPtr<Poco::XML::Text> pMessageIdText = pDoc->createTextNode(messageId);
        pMessageId->appendChild(pMessageIdText);

        // MD5 body
        Poco::XML::AutoPtr<Poco::XML::Element> pMd5Body = pDoc->createElement("MD5OfMessageBody");
        pSendMessageResult->appendChild(pMd5Body);
        Poco::XML::AutoPtr<Poco::XML::Text> pMd5BodyText = pDoc->createTextNode(md5Body);
        pMd5Body->appendChild(pMd5BodyText);

        // MD5 user attributes
        Poco::XML::AutoPtr<Poco::XML::Element> pMd5UserAttr = pDoc->createElement("MD5OfMessageAttributes");
        pSendMessageResult->appendChild(pMd5UserAttr);
        Poco::XML::AutoPtr<Poco::XML::Text> pMd5UserAttrText = pDoc->createTextNode(md5UserAttr);
        pMd5UserAttr->appendChild(pMd5UserAttrText);

        // MD5 system attributes
        Poco::XML::AutoPtr<Poco::XML::Element> pMd5SystemAttr = pDoc->createElement("MD5OfMessageSystemAttributes");
        pSendMessageResult->appendChild(pMd5SystemAttr);
        Poco::XML::AutoPtr<Poco::XML::Text> pMd5SystemAttrText = pDoc->createTextNode(md5SystemAttr);
        pMd5SystemAttr->appendChild(pMd5SystemAttrText);

        // MD5 system attributes
        Poco::XML::AutoPtr<Poco::XML::Element> pSequenceNr = pDoc->createElement("SequenceNumber");
        pSendMessageResult->appendChild(pSequenceNr);
        Poco::XML::AutoPtr<Poco::XML::Text> pSequenceNrText = pDoc->createTextNode(sequenceNumber);
        pSequenceNr->appendChild(pSequenceNrText);

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
        pRoot->appendChild(pMetaData);

        Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
        pMetaData->appendChild(pRequestId);
        Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(requestId);
        pRequestId->appendChild(pRequestText);
*/
        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.writeNode(output, pDoc);
        return output.str();
    }

    std::string SendMessageBatchResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SendMessageBatchResponse &r) {
        os << "SendMessageBatchResponse=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
