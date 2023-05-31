//
// Created by vogje01 on 31/05/2023.
//

#include "awsmock/dto/s3/RestErrorResponse.h"

namespace AwsMock::Dto::Common {

    RestErrorResponse::RestErrorResponse(const std::string &code, const std::string &message, const std::string &resource, const std::string &requestId) :
        _code(code), _message(message), _resource(resource), _requestId(requestId) {
    }

    std::string RestErrorResponse::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

        // Root <Error>
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Error");
        pDoc->appendChild(pRoot);

        // Code <code>
        Poco::XML::AutoPtr<Poco::XML::Element> pCode = pDoc->createElement("Code");
        pRoot->appendChild(pCode);
        Poco::XML::AutoPtr<Poco::XML::Text> pCodeText = pDoc->createTextNode(_code);
        pCode->appendChild(pCodeText);

        // Message <message>
        Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
        pRoot->appendChild(pCode);
        Poco::XML::AutoPtr<Poco::XML::Text> pMessageText = pDoc->createTextNode(_message);
        pMessage->appendChild(pMessageText);

        // Resource <resource>
        Poco::XML::AutoPtr<Poco::XML::Element> pResource = pDoc->createElement("Resource");
        pRoot->appendChild(pCode);
        Poco::XML::AutoPtr<Poco::XML::Text> pResourceText = pDoc->createTextNode(_resource);
        pResource->appendChild(pResourceText);

        // Resource <resource>
        Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
        pRoot->appendChild(pCode);
        Poco::XML::AutoPtr<Poco::XML::Text> pRequestIdText = pDoc->createTextNode(_requestId);
        pRequestId->appendChild(pRequestIdText);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        return output.str();
    }
}
