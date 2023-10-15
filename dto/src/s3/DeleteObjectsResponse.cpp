//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsResponse.h>

namespace AwsMock::Dto::S3 {

  std::string DeleteObjectsResponse::ToXml() const {

    // Root
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("DeleteResult");
    pDoc->appendChild(pRoot);

    for (const auto &it : keys) {

      // Deleted
      Poco::XML::AutoPtr<Poco::XML::Element> pDeleted = pDoc->createElement("Deleted");
      pRoot->appendChild(pDeleted);

      // Key
      Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
      pDeleted->appendChild(pKey);
      Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(it);
      pKey->appendChild(pKeyText);
    }

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(output, pDoc);

    return output.str();
  }

  std::string DeleteObjectsResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteObjectsResponse &r) {
    os << "DeleteObjectsResponse={";
    for (auto &it : r.keys) {
      os << "' key='" + it;
    }
    os << "'}";
    return os;
  }

} // namespace AwsMock::Dto
