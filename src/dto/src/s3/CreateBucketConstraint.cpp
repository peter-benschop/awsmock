//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketConstraint.h>

namespace AwsMock::Dto::S3 {

  std::string CreateBucketConstraint::ToXml() const {
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketConfiguration");
    pDoc->appendChild(pRoot);

    Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("LocationConstraint");
    pRoot->appendChild(pLocation);
    Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(location);
    pLocation->appendChild(pLocationText);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(output, pDoc);

    return output.str();
  }

  std::string CreateBucketConstraint::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateBucketConstraint &r) {
    os << "CreateBucketConstraint={location='" + r.location + "'}";
    return os;
  }

} // namespace AwsMock::Dto
