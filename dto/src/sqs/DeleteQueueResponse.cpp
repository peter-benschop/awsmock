//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueResponse.h>

namespace AwsMock::Dto::SQS {

  Core::LogStream DeleteQueueResponse::_logger = Core::LogStream(Poco::Logger::get("DeleteQueueResponse"));

  std::string DeleteQueueResponse::ToXml() {

    try {
      // Root
      Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
      Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("DeleteQueueResponse");
      pDoc->appendChild(pRoot);

      // Metadata
      Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
      pRoot->appendChild(pMetaData);

      Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
      pMetaData->appendChild(pRequestId);
      Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(Poco::UUIDGenerator().createRandom().toString());
      pRequestId->appendChild(pRequestText);

      std::stringstream output;
      Poco::XML::DOMWriter writer;
      writer.setNewLine("\n");
      writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
      writer.writeNode(output, pDoc);

      return output.str();
    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "SQS XML conversion error: " << exc.message() << std::endl;
    }
    return {};
  }

  std::string DeleteQueueResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteQueueResponse &r) {
    os << "DeleteQueueResponse={name='" + r._queue.name + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
