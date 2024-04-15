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

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string CompleteMultipartUploadResult::ToXml() const {
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CompleteMultipartUploadResult");
    pDoc->appendChild(pRoot);

    Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("Location");
    pRoot->appendChild(pLocation);
    Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(location);
    pLocation->appendChild(pLocationText);

    Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
    pRoot->appendChild(pBucket);
    Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(bucket);
    pBucket->appendChild(pBucketText);

    Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
    pRoot->appendChild(pKey);
    Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(key);
    pKey->appendChild(pKeyText);

    Poco::XML::AutoPtr<Poco::XML::Element> pEtag = pDoc->createElement("ETag");
    pRoot->appendChild(pEtag);
    Poco::XML::AutoPtr<Poco::XML::Text> pEtagText = pDoc->createTextNode(etag);
    pEtag->appendChild(pEtagText);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.writeNode(output, pDoc);

    return output.str();
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
