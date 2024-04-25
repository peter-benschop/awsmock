//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/GetTopicAttributesResponse.h>

namespace AwsMock::Dto::SNS {

    std::string GetTopicAttributesResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetTopicAttributesResponse");
        pDoc->appendChild(pRoot);

        // CreateQueueResult
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicAttributesResult = pDoc->createElement("GetTopicAttributesResult");
        pRoot->appendChild(pTopicAttributesResult);

        Poco::XML::AutoPtr<Poco::XML::Element> pAttributes = pDoc->createElement("Attributes");
        pTopicAttributesResult->appendChild(pAttributes);

        // Topic ARN
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicArnEntry = pDoc->createElement("entry");
        pAttributes->appendChild(pTopicArnEntry);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicArnKey = pDoc->createElement("key");
        pTopicArnEntry->appendChild(pTopicArnKey);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicArnKeyText = pDoc->createTextNode("TopicArn");
        pTopicArnKey->appendChild(pTopicArnKeyText);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicArnValue = pDoc->createElement("value");
        pTopicArnEntry->appendChild(pTopicArnValue);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicArnValueText = pDoc->createTextNode(topicArn);
        pTopicArnValue->appendChild(pTopicArnValueText);

        // Owner
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicOwnerEntry = pDoc->createElement("entry");
        pAttributes->appendChild(pTopicOwnerEntry);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicOwnerKey = pDoc->createElement("key");
        pTopicOwnerEntry->appendChild(pTopicOwnerKey);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicOwnerKeyText = pDoc->createTextNode("Owner");
        pTopicOwnerKey->appendChild(pTopicOwnerKeyText);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicOwnerValue = pDoc->createElement("value");
        pTopicOwnerEntry->appendChild(pTopicOwnerValue);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicOwnerValueText = pDoc->createTextNode(owner);
        pTopicOwnerValue->appendChild(pTopicOwnerValueText);

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

    std::string GetTopicAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetTopicAttributesResponse &r) {
        os << "GetTopicAttributesResponse={region='" << r.region << "', topicName='" << r.topicName << "', owner='" << r.owner << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
