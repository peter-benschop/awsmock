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

        // Display name
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicDisplayNameEntry = pDoc->createElement("entry");
        pAttributes->appendChild(pTopicDisplayNameEntry);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicDisplayNameKey = pDoc->createElement("key");
        pTopicDisplayNameEntry->appendChild(pTopicDisplayNameKey);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicDisplayNameKeyText = pDoc->createTextNode("DisplayName");
        pTopicDisplayNameKey->appendChild(pTopicDisplayNameKeyText);
        Poco::XML::AutoPtr<Poco::XML::Element> pTopicDisplayNameValue = pDoc->createElement("value");
        pTopicDisplayNameEntry->appendChild(pTopicDisplayNameValue);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicDisplayNameValueText = pDoc->createTextNode(displayName);
        pTopicDisplayNameValue->appendChild(pTopicDisplayNameValueText);

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
        pRoot->appendChild(pMetaData);

        Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
        pMetaData->appendChild(pRequestId);
        Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(Poco::UUIDGenerator().createRandom().toString());
        pRequestId->appendChild(pRequestText);

        return Core::XmlUtils::ToXmlString(pDoc);
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
