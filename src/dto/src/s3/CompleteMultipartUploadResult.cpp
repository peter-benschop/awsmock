//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

  std::string CompleteMultipartUploadResult::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("location", location);
      rootJson.set("bucket", bucket);
      rootJson.set("key", key);
      rootJson.set("etag", etag);
      rootJson.set("checksumCrc32", checksumCrc32);
      rootJson.set("checksumCrc32c", checksumCrc32c);
      rootJson.set("checksumSha1", checksumSha1);
      rootJson.set("checksumSha256", checksumSha256);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string CompleteMultipartUploadResult::ToXml() const {

    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "CompleteMultipartUploadResult");

    Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Location", location);
    Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Bucket", bucket);
    Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Key", key);
    Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ETag", etag);

    return Core::XmlUtils::ToXmlString(pDoc);
  }

  std::string CompleteMultipartUploadResult::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadResult &r) {
    os << "CompleteMultipartUploadResult=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto
