//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sqs/ReceiveMessageResponse.h>

namespace AwsMock::Dto::SQS {

  std::string ReceiveMessageResponse::ToXml() const {

    // Root
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ReceiveMessageResponse");
    pDoc->appendChild(pRoot);

    // ReceiveMessageResult
    Poco::XML::AutoPtr<Poco::XML::Element> pResult = pDoc->createElement("ReceiveMessageResult");
    pRoot->appendChild(pResult);

    for (auto &it : messageList) {

      // Message
      Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
      pResult->appendChild(pMessage);

      // MessageId
      Poco::XML::AutoPtr<Poco::XML::Element> pMessageId = pDoc->createElement("MessageId");
      pMessage->appendChild(pMessageId);
      Poco::XML::AutoPtr<Poco::XML::Text> pMessageIdText = pDoc->createTextNode(it.messageId);
      pMessageId->appendChild(pMessageIdText);

      // ReceiptHandle
      Poco::XML::AutoPtr<Poco::XML::Element> pReceiptHandle = pDoc->createElement("ReceiptHandle");
      pMessage->appendChild(pReceiptHandle);
      Poco::XML::AutoPtr<Poco::XML::Text> pReceiptHandleText = pDoc->createTextNode(it.receiptHandle);
      pReceiptHandle->appendChild(pReceiptHandleText);

      // MD5OfBody
      Poco::XML::AutoPtr<Poco::XML::Element> pMd5Body = pDoc->createElement("MD5OfBody");
      pMessage->appendChild(pMd5Body);
      Poco::XML::AutoPtr<Poco::XML::Text> pMd5BodyText = pDoc->createTextNode(it.md5Body);
      pMd5Body->appendChild(pMd5BodyText);

      // Body
      Poco::XML::AutoPtr<Poco::XML::Element> pBody = pDoc->createElement("Body");
      pMessage->appendChild(pBody);
      Poco::XML::AutoPtr<Poco::XML::Text> pBodyText = pDoc->createTextNode(it.body);
      pBody->appendChild(pBodyText);

      for (auto &at : it.attributes) {

        // MessageAttribute
        Poco::XML::AutoPtr<Poco::XML::Element> pAttribute = pDoc->createElement("Attribute");
        pMessage->appendChild(pAttribute);

        // Name
        Poco::XML::AutoPtr<Poco::XML::Element> pAttrName = pDoc->createElement("Name");
        pAttribute->appendChild(pAttrName);
        Poco::XML::AutoPtr<Poco::XML::Text> pAttrNameText = pDoc->createTextNode(at.attributeName);
        pAttrName->appendChild(pAttrNameText);

        // Value
        Poco::XML::AutoPtr<Poco::XML::Element> pAttrValue = pDoc->createElement("Value");
        pAttribute->appendChild(pAttrValue);
        Poco::XML::AutoPtr<Poco::XML::Text> pAttrValueText = pDoc->createTextNode(at.attributeValue);
        pAttrValue->appendChild(pAttrValueText);
      }
    }

    // Metadata
    Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
    pRoot->appendChild(pMetaData);

    Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
    pMetaData->appendChild(pRequestId);
    Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(requestId);
    pRequestId->appendChild(pRequestText);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    //writer.setNewLine("\n");
    //writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(output, pDoc);
    //std::cout << output.str() << std::endl;

    return output.str();
  }

  std::string ReceiveMessageResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ReceiveMessageResponse &r) {
    os << "ReceiveMessageResponse={resource='" << r.resource << "', requestId: '" << r.requestId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
