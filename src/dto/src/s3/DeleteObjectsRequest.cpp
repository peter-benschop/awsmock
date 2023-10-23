//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsRequest.h>

namespace AwsMock::Dto::S3 {

  DeleteObjectsRequest::DeleteObjectsRequest(const std::string &xmlString) {
    FromXml(xmlString);
  }

  void DeleteObjectsRequest::FromXml(const std::string &xmlString) {

    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

    Poco::XML::Node *deleteNode = pDoc->getNodeByPath("/Delete");
    if (deleteNode) {

      for (unsigned long i = 0; i < deleteNode->childNodes()->length(); i++) {
        Poco::XML::Node *objectNode = deleteNode->childNodes()->item(i);
        keys.push_back(objectNode->innerText());
      }
    }
  }

  std::string DeleteObjectsRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteObjectsRequest &r) {
    os << "DeleteObjectsRequest={region='" + r.region + "' bucket='" + r.bucket;
    for (auto &it : r.keys) {
      os << "' key='" + it;
    }
    os << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
