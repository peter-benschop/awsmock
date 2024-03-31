//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

  void CreateMultipartUploadRequest::FromXml(const std::string &xmlString) {

    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

    Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
    region = node->innerText();
  }

  std::string CreateMultipartUploadRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadRequest &r) {
    os << "CreateMultipartUploadRequest={region='" << r.region << "', bucket='" << r.bucket << "', key='" << r.key << "', user='" << r.user << "', uploadId='" << r.uploadId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::s3
