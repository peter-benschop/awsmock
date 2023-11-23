//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketResponse.h>

namespace AwsMock::Dto::S3 {

  std::string CreateBucketResponse::ToXml() const {
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketResult");
    pDoc->appendChild(pRoot);

    // Bucket ARN
    Poco::XML::AutoPtr<Poco::XML::Element> pArn = pDoc->createElement("BucketArn");
    pRoot->appendChild(pArn);
    Poco::XML::AutoPtr<Poco::XML::Text> pArnText = pDoc->createTextNode(arn);
    pArn->appendChild(pArnText);

    // Bucket location
    Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("Location");
    pRoot->appendChild(pLocation);
    Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(arn);
    pLocation->appendChild(pLocationText);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION);
    writer.writeNode(output, pDoc);

    return output.str();
  }

  std::string CreateBucketResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateBucketResponse &r) {
    os << "CreateBucketResponse={bucket='" + r.location + "', arn='" + r.arn + "'}";
    return os;
  }

} // namespace AwsMock::Dto
