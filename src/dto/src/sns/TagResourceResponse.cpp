//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/TagResourceResponse.h>

namespace AwsMock::Dto::SNS {

    std::string TagResourceResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("TagResourceResponse");
        pDoc->appendChild(pRoot);

        // CreateQueueResult
        Poco::XML::AutoPtr<Poco::XML::Element> pTagResourceResult = pDoc->createElement("TagResourceResult");
        pRoot->appendChild(pTagResourceResult);

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
    }

    std::string TagResourceResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagResourceResponse &r) {
        os << "TagResourceResponse={}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
