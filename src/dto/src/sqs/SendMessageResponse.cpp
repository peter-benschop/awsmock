//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageResponse.h>

namespace AwsMock::Dto::SQS {

  std::string SendMessageResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("MessageId", messageId);
      rootJson.set("MD5OfMessageBody", md5Body);
      rootJson.set("MD5OfMessageAttributes", md5UserAttr);
      rootJson.set("MD5OfMessageSystemAttributes", md5SystemAttr);
      rootJson.set("SequenceNumber", sequenceNumber);

      std::ostringstream os;
      rootJson.stringify(os);
      std::string tmp = os.str();
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void SendMessageResponse::FromJson(const std::string &jsonString) {

    try {
      Poco::JSON::Parser parser;
      Poco::Dynamic::Var result = parser.parse(jsonString);

      const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
      Core::JsonUtils::GetJsonValueString("MessageId", rootObject, messageId);
      Core::JsonUtils::GetJsonValueString("MD5OfMessageBody", rootObject, md5Body);
      Core::JsonUtils::GetJsonValueString("MD5OfMessageAttributes", rootObject, md5UserAttr);
      Core::JsonUtils::GetJsonValueString("MD5OfMessageSystemAttributes", rootObject, md5SystemAttr);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void SendMessageResponse::FromXml(const std::string &xmlString) {

    Poco::XML::DOMParser parser;
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
    }
  }

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

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.writeNode(output, pDoc);
    return output.str();
  }

  std::string SendMessageResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SendMessageResponse &r) {
    os << "SendMessageResponse={id='" << r.id << "', url='" << r.queueUrl << "', messageId='" << r.messageId << "', receiptHandle='" << r.receiptHandle
       << "', md5body='" << r.md5Body << "', md5UserAttr='" << r.md5UserAttr << "', md5SystemAttr='" << r.md5SystemAttr << "', requestId: '" << r.requestId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
