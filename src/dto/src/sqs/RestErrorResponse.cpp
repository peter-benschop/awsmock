//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/sqs/RestErrorResponse.h>

namespace AwsMock::Dto::SQS {

  RestErrorResponse::RestErrorResponse(const Core::ServiceException &exc) {
    message = exc.message();
    code = exc.code();
    if (exc.requestId()) {
      requestId = std::string(exc.requestId());
    }
    if (exc.resource()) {
      requestId = std::string(exc.resource());
    }
  }

  std::string RestErrorResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      Poco::JSON::Object errorResponseObject;

      errorResponseObject.set("Type", "Sender");
      errorResponseObject.set("Code", code);
      errorResponseObject.set("Message", message);
      errorResponseObject.set("Resource", resource);

      rootJson.set("ErrorResponse", errorResponseObject);

      if (!requestId.empty()) {
        rootJson.set("RequestId", requestId);
      }

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string RestErrorResponse::ToXml() const {
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

    // ErrorResponse
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ErrorResponse");
    pDoc->appendChild(pRoot);

    // Error
    Poco::XML::AutoPtr<Poco::XML::Element> pError = pDoc->createElement("Error");
    pRoot->appendChild(pError);

    // Type
    Poco::XML::AutoPtr<Poco::XML::Element> pType = pDoc->createElement("Type");
    pError->appendChild(pType);
    Poco::XML::AutoPtr<Poco::XML::Text> pTypeText = pDoc->createTextNode("Sender");
    pType->appendChild(pTypeText);

    // Code
    Poco::XML::AutoPtr<Poco::XML::Element> pCode = pDoc->createElement("Code");
    pError->appendChild(pCode);
    Poco::XML::AutoPtr<Poco::XML::Text> pCodeText = pDoc->createTextNode(std::to_string(code));
    pCode->appendChild(pCodeText);

    // Message <Message>
    Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
    pError->appendChild(pMessage);
    Poco::XML::AutoPtr<Poco::XML::Text> pMessageText = pDoc->createTextNode(message);
    pMessage->appendChild(pMessageText);

    // Resource <Resource>
    if (!resource.empty()) {
      Poco::XML::AutoPtr<Poco::XML::Element> pResource = pDoc->createElement("Resource");
      pRoot->appendChild(pResource);
      Poco::XML::AutoPtr<Poco::XML::Text> pResourceText = pDoc->createTextNode(resource);
      pResource->appendChild(pResourceText);
    }

    // RequestId <RequestId>
    if (!requestId.empty()) {
      Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
      pRoot->appendChild(pRequestId);
      Poco::XML::AutoPtr<Poco::XML::Text> pRequestIdText = pDoc->createTextNode(requestId);
      pRequestId->appendChild(pRequestIdText);
    }

    std::stringstream output;
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(output, pDoc);

    return output.str();
  }

  std::string RestErrorResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const RestErrorResponse &r) {
    os << "RestErrorResponse={code='" + std::to_string(r.code) + "' message='" + r.message + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
