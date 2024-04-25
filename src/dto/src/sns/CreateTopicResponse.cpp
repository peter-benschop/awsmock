//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/CreateTopicResponse.h>

namespace AwsMock::Dto::SNS {

    std::string CreateTopicResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateTopicResponse");
        pDoc->appendChild(pRoot);

        // CreateQueueResult
        Poco::XML::AutoPtr<Poco::XML::Element> pListQueueResult = pDoc->createElement("CreateTopicResult");
        pRoot->appendChild(pListQueueResult);

        Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrl = pDoc->createElement("TopicArn");
        pListQueueResult->appendChild(pQueueUrl);
        Poco::XML::AutoPtr<Poco::XML::Text> pQueueUrlText = pDoc->createTextNode(topicArn);
        pQueueUrl->appendChild(pQueueUrlText);

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

    std::string CreateTopicResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTopicResponse &r) {
        os << "CreateTopicResponse={region='" << r.region << "', name='" << r.name << "', owner='" << r.owner << "', topicArn='" << r.topicArn << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
