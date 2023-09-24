//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageResponse.h>

namespace AwsMock::Dto::SQS {

    std::string SendMessageResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("SendMessageResponse");
        pDoc->appendChild(pRoot);

        // SendMessageResult
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

        // MD5 sqs
        Poco::XML::AutoPtr<Poco::XML::Element> pMd5Attr = pDoc->createElement("MD5OfMessageAttributes");
        pSendMessageResult->appendChild(pMd5Attr);
        Poco::XML::AutoPtr<Poco::XML::Text> pMd5AttrText = pDoc->createTextNode(md5Attr);
        pMd5Attr->appendChild(pMd5AttrText);

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
        pRoot->appendChild(pMetaData);

        Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
        pMetaData->appendChild(pRequestId);
        Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(Poco::UUIDGenerator().createRandom().toString());
        pRequestId->appendChild(pRequestText);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);
        std::cerr << output.str()<< std::endl;
        return output.str();
    }

    std::string SendMessageResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SendMessageResponse &r) {
        os << "SendMessageResponse={id='" << r.id << "', url='" << r.queueUrl << "', messageId='" << r.messageId << "', receiptHandle='" << r.receiptHandle <<
           "', md5body='" << r.md5Body << "', md5attr='" << r.md5Attr << "'}";
        return os;
    }

} // namespace AwsMock::Dto::SQS
