//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListSubscriptionsByTopicResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListSubscriptionsByTopicResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListSubscriptionsByTopicResponse");
        pDoc->appendChild(pRoot);

        // CreateQueueResult
        Poco::XML::AutoPtr<Poco::XML::Element> pSubscriptionByTopicResult = pDoc->createElement("ListSubscriptionsByTopicResult");
        pRoot->appendChild(pSubscriptionByTopicResult);

        Poco::XML::AutoPtr<Poco::XML::Element> pSubscriptions = pDoc->createElement("Subscriptions");
        pSubscriptionByTopicResult->appendChild(pSubscriptions);

        for (const auto &subscription: subscriptions) {
            Poco::XML::AutoPtr<Poco::XML::Element> pMember = pDoc->createElement("member");
            pSubscriptions->appendChild(pMember);

            // Topic ARN
            Poco::XML::AutoPtr<Poco::XML::Element> pTopicArn = pDoc->createElement("TopicArn");
            pMember->appendChild(pTopicArn);
            Poco::XML::AutoPtr<Poco::XML::Text> pTopicArnText = pDoc->createTextNode(subscription.topicArn);
            pTopicArn->appendChild(pTopicArnText);

            // Protocol
            Poco::XML::AutoPtr<Poco::XML::Element> pProtocol = pDoc->createElement("Protocol");
            pMember->appendChild(pProtocol);
            Poco::XML::AutoPtr<Poco::XML::Text> pProtocolText = pDoc->createTextNode(subscription.protocol);
            pProtocol->appendChild(pProtocolText);

            // Subscription ARN
            Poco::XML::AutoPtr<Poco::XML::Element> pSubscriptionArn = pDoc->createElement("SubscriptionArn");
            pMember->appendChild(pSubscriptionArn);
            Poco::XML::AutoPtr<Poco::XML::Text> pSubscriptionArnText = pDoc->createTextNode(subscription.subscriptionArn);
            pSubscriptionArn->appendChild(pSubscriptionArnText);

            // Owner
            Poco::XML::AutoPtr<Poco::XML::Element> pEndpoint = pDoc->createElement("Endpoint");
            pMember->appendChild(pEndpoint);
            Poco::XML::AutoPtr<Poco::XML::Text> pEndpointText = pDoc->createTextNode(subscription.endpoint);
            pEndpoint->appendChild(pEndpointText);

            // Owner
            Poco::XML::AutoPtr<Poco::XML::Element> pOwner = pDoc->createElement("Owner");
            pMember->appendChild(pOwner);
            Poco::XML::AutoPtr<Poco::XML::Text> pOwnerText = pDoc->createTextNode(subscription.owner);
            pOwner->appendChild(pOwnerText);
        }

        // Total
        Poco::XML::AutoPtr<Poco::XML::Element> pNextToken = pDoc->createElement("NextToken");
        pSubscriptionByTopicResult->appendChild(pNextToken);
        Poco::XML::AutoPtr<Poco::XML::Text> pNextTokenText = pDoc->createTextNode(nextToken);
        pNextToken->appendChild(pNextTokenText);

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

    std::string ListSubscriptionsByTopicResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicResponse &r) {
        os << "ListSubscriptionsByTopicResponse={region='" << r.region << "', topicArn='" << r.topicArn << "', subscriptions=[";
        for (const auto &s: r.subscriptions) {
            os << "topicArn='" << s.topicArn << "', protocol='" << s.protocol << "', subscrptionArn='" << s.subscriptionArn << "', endpoint='" << s.endpoint << "', owner='" << s.owner << "', ";
        }
        os.seekp(-2, std::ostream::cur);
        os << "]}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
