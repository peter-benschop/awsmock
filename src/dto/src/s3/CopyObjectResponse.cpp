//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectResponse.h>

namespace AwsMock::Dto::S3 {

  std::string CopyObjectResponse::ToXml() const {

    // Root
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CopyObjectResult");
    pDoc->appendChild(pRoot);

    // ETag
    Poco::XML::AutoPtr<Poco::XML::Element> pETag = pDoc->createElement("ETag");
    pRoot->appendChild(pETag);
    Poco::XML::AutoPtr<Poco::XML::Text> pETagText = pDoc->createTextNode(eTag);
    pETag->appendChild(pETagText);

    // LastModified
    Poco::XML::AutoPtr<Poco::XML::Element> pLastModified = pDoc->createElement("LastModified");
    pRoot->appendChild(pLastModified);
    Poco::XML::AutoPtr<Poco::XML::Text> pLastModifiedTest = pDoc->createTextNode(lastModified);
    pLastModified->appendChild(pLastModifiedTest);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.writeNode(output, pDoc);

    return output.str();
  }

  std::string CopyObjectResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CopyObjectResponse &r) {
    os << "CopyObjectResponse={eTag:'" + r.eTag + "'}";
    return os;
  }

} // namespace AwsMock::Dto
