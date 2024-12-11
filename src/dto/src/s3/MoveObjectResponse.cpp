//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/MoveObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string MoveObjectResponse::ToXml() const {

        // Todo:
        /*
        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("MoveObjectResult");
        pDoc->appendChild(pRoot);

        // ETag
        Poco::XML::AutoPtr<Poco::XML::Element> pETag = pDoc->createElement("ETag");
        pRoot->appendChild(pETag);
        Poco::XML::AutoPtr<Poco::XML::Text> pETagText = pDoc->createTextNode(eTag);
        pETag->appendChild(pETagText);

        // LastModified
        Poco::XML::AutoPtr<Poco::XML::Element> pLastModified = pDoc->createElement("LastModified");
        pRoot->appendChild(pLastModified);
        Poco::XML::AutoPtr<Poco::XML::Text> pLastModifiedTest = pDoc->createTextNode(lastModified);
        pLastModified->appendChild(pLastModifiedTest);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION);
        writer.writeNode(output, pDoc);

        return output.str();*/
        return {};
    }

    std::string MoveObjectResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MoveObjectResponse &r) {
        os << "MoveObjectResponse={eTag:'" + r.eTag + "'}";
        return os;
    }

}// namespace AwsMock::Dto::S3
