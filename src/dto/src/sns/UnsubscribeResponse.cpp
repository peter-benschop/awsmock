//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/UnsubscribeResponse.h>

namespace AwsMock::Dto::SNS {

  std::string UnsubscribeResponse::ToXml() {

    // Root
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("UnsubscribeResponse");
    pDoc->appendChild(pRoot);

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

  std::string UnsubscribeResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UnsubscribeResponse &r) {
    os << "UnsubscribeResponse={subscriptionArn='" + r.subscriptionArn + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SNS
