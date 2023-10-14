//
// Created by vogje01 on 13/10/2023.
//

#include <awsmock/dto/s3/PutBucketVersioningRequest.h>

namespace AwsMock::Dto::S3 {

  PutBucketVersioningRequest::PutBucketVersioningRequest(const std::string &xmlString) {
    FromXml(xmlString);
  }

  void PutBucketVersioningRequest::FromXml(const std::string &xmlString) {

    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

    Poco::XML::Node *node = pDoc->getNodeByPath("/VersioningConfiguration/Status");
    status = node->innerText();
  }

  std::string PutBucketVersioningRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PutBucketVersioningRequest &r) {
    os << "PutBucketVersioningRequest={region='" << r.region << "', user='" << r.user << "', bucket='" << r.bucket << "', status='" << r.status << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
