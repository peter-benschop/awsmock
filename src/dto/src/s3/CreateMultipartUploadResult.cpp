//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

  std::string CreateMultipartUploadResult::ToXml() const {
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateMultipartUploadResult");
    pDoc->appendChild(pRoot);

    Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
    pRoot->appendChild(pBucket);
    Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(bucket);
    pBucket->appendChild(pBucketText);

    Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
    pRoot->appendChild(pKey);
    Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(key);
    pKey->appendChild(pKeyText);

    Poco::XML::AutoPtr<Poco::XML::Element> pUploadId = pDoc->createElement("UploadId");
    pRoot->appendChild(pUploadId);
    Poco::XML::AutoPtr<Poco::XML::Text> pUploadIdText = pDoc->createTextNode(uploadId);
    pUploadId->appendChild(pUploadIdText);

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(output, pDoc);

    return output.str();
  }

  void CreateMultipartUploadResult::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("Bucket", rootObject, bucket);
      Core::JsonUtils::GetJsonValueString("Key", rootObject, key);
      Core::JsonUtils::GetJsonValueString("UploadId", rootObject, uploadId);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  /**
   * Converts the DTO to a string representation.
   *
   * @return DTO as string for logging.
   */
  std::string CreateMultipartUploadResult::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  /**
   * Stream provider.
   *
   * @return output stream
   */
  std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadResult &r) {
    os << "CreateMultipartUploadResult={bucket='" + r.bucket + "', key='" + r.key + "', uploadId='" + r.uploadId + "'}";
    return os;
  }

} // namespace AwsMock::Dto
