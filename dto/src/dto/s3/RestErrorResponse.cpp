//
// Created by vogje01 on 31/05/2023.
//

#include <utility>

#include "awsmock/dto/s3/RestErrorResponse.h"

namespace AwsMock::Dto::Common {

    RestErrorResponse::RestErrorResponse(std::string code, std::string message, std::string resource, std::string requestId) :
        _code(std::move(code)), _message(std::move(message)), _resource(std::move(resource)), _requestId(std::move(requestId)) {
    }

    std::string RestErrorResponse::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

        // Root <Error>
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Error");
        pDoc->appendChild(pRoot);

        // Code <Code>
        Poco::XML::AutoPtr<Poco::XML::Element> pCode = pDoc->createElement("Code");
        pRoot->appendChild(pCode);
        Poco::XML::AutoPtr<Poco::XML::Text> pCodeText = pDoc->createTextNode(_code);
        pCode->appendChild(pCodeText);

        // Message <Message>
        Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
        pRoot->appendChild(pMessage);
        Poco::XML::AutoPtr<Poco::XML::Text> pMessageText = pDoc->createTextNode(_message);
        pMessage->appendChild(pMessageText);

        // Resource <Resource>
        if(!_resource.empty()) {
            Poco::XML::AutoPtr<Poco::XML::Element> pResource = pDoc->createElement("Resource");
            pRoot->appendChild(pResource);
            Poco::XML::AutoPtr<Poco::XML::Text> pResourceText = pDoc->createTextNode(_resource);
            pResource->appendChild(pResourceText);
        }

        // RequestId <RequestId>
        if(!_requestId.empty()) {
            Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
            pRoot->appendChild(pRequestId);
            Poco::XML::AutoPtr<Poco::XML::Text> pRequestIdText = pDoc->createTextNode(_requestId);
            pRequestId->appendChild(pRequestIdText);
        }

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::cerr << "Error: " << output.rdbuf() << std::endl;

        return output.str();
    }
}
