//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/sqs/RestErrorResponse.h>

namespace AwsMock::Dto::SQS {

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
            throw Core::ServiceException(exc.message());
        }
    }

    std::string RestErrorResponse::ToXml() const {
        Poco::XML::AutoPtr pDoc = new Poco::XML::Document;

        // ErrorResponse
        Poco::XML::AutoPtr pRoot = pDoc->createElement("ErrorResponse");
        pDoc->appendChild(pRoot);

        // Error
        Poco::XML::AutoPtr pError = pDoc->createElement("Error");
        pRoot->appendChild(pError);

        // Type
        Poco::XML::AutoPtr pType = pDoc->createElement("Type");
        pError->appendChild(pType);
        Poco::XML::AutoPtr pTypeText = pDoc->createTextNode("Sender");
        pType->appendChild(pTypeText);

        // Code
        Poco::XML::AutoPtr pCode = pDoc->createElement("Code");
        pError->appendChild(pCode);
        Poco::XML::AutoPtr pCodeText = pDoc->createTextNode(std::to_string(code));
        pCode->appendChild(pCodeText);

        // Message <Message>
        Poco::XML::AutoPtr pMessage = pDoc->createElement("Message");
        pError->appendChild(pMessage);
        Poco::XML::AutoPtr pMessageText = pDoc->createTextNode(message);
        pMessage->appendChild(pMessageText);

        // Resource <Resource>
        if (!resource.empty()) {
            Poco::XML::AutoPtr pResource = pDoc->createElement("Resource");
            pRoot->appendChild(pResource);
            Poco::XML::AutoPtr pResourceText = pDoc->createTextNode(resource);
            pResource->appendChild(pResourceText);
        }

        // RequestId <RequestId>
        if (!requestId.empty()) {
            Poco::XML::AutoPtr pRequestId = pDoc->createElement("RequestId");
            pRoot->appendChild(pRequestId);
            Poco::XML::AutoPtr pRequestIdText = pDoc->createTextNode(requestId);
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
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RestErrorResponse &r) {
        os << "RestErrorResponse={code='" + std::to_string(r.code) + "' message='" + r.message + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
