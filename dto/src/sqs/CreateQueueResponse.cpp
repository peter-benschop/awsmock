//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueResponse.h>

namespace AwsMock::Dto::SQS {

  std::string CreateQueueResponse::ToXml() const {

    // Root
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateQueueResponse");
    pDoc->appendChild(pRoot);

    // CreateQueueResult
    Poco::XML::AutoPtr<Poco::XML::Element> pListQueueResult = pDoc->createElement("CreateQueueResult");
    pRoot->appendChild(pListQueueResult);

    Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrl = pDoc->createElement("QueueUrl");
    pListQueueResult->appendChild(pQueueUrl);
    Poco::XML::AutoPtr<Poco::XML::Text> pQueueUrlText = pDoc->createTextNode(queueUrl);
    pQueueUrl->appendChild(pQueueUrlText);

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

    return output.str();
  }

  std::string CreateQueueResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateQueueResponse &r) {
    os << "CreateQueueResponse={region='" << r.region << "' name='" << r.name << "' owner='" << r.owner << "' url='" << r.queueUrl << "', arn='" << r.queueArn
       << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
