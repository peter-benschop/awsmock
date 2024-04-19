//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsRequest.h>

namespace AwsMock::Dto::S3 {

  std::string DeleteObjectsRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("bucket", bucket);
      rootJson.set("keys", Core::JsonUtils::GetJsonStringArray(keys));

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
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
    os << "DeleteObjectsRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::S3
