//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketResponse.h>

namespace AwsMock::Dto::S3 {


  std::string CreateBucketResponse::ToXml() const {
      Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
      Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketResult");
      pDoc->appendChild(pRoot);
      Poco::XML::AutoPtr<Poco::XML::Element> pChild1 = pDoc->createElement("BucketArn");
      pRoot->appendChild(pChild1);
      Poco::XML::AutoPtr<Poco::XML::Text> pText1 = pDoc->createTextNode(arn);
      pChild1->appendChild(pText1);

      std::stringstream output;
      Poco::XML::DOMWriter writer;
      writer.setNewLine("\n");
      writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
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
