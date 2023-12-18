//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListTopicsResponse.h>

namespace AwsMock::Dto::SNS {

  std::string ListTopicsResponse::ToXml() const {

      // XML Document
      Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

      // Root element
      Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListTopicsResponse");
      pDoc->appendChild(pRoot);

      // ListTopicsResult
      Poco::XML::AutoPtr<Poco::XML::Element> pListTopicResult = pDoc->createElement("ListTopicsResult");
      pRoot->appendChild(pListTopicResult);

      Poco::XML::AutoPtr<Poco::XML::Element> pTopics = pDoc->createElement("Topics");
      pListTopicResult->appendChild(pTopics);

      for (auto &it : topicList) {

        Poco::XML::AutoPtr<Poco::XML::Element> pTopicMember = pDoc->createElement("member");
        pTopics->appendChild(pTopicMember);

        Poco::XML::AutoPtr<Poco::XML::Element> pTopicArn = pDoc->createElement("TopicArn");
        pTopicMember->appendChild(pTopicArn);
        Poco::XML::AutoPtr<Poco::XML::Text> pTopicArnText = pDoc->createTextNode(it.topicArn);
        pTopicArn->appendChild(pTopicArnText);
      }

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

    std::string ListTopicsResponse::ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTopicsResponse &r) {
      os << "ListTopicsResponse={topicList=[";
      for (auto &l : r.topicList) {
        os << l.ToString();
      }
      os << "]}";
      return os;
    }

} // namespace AwsMock::Dto::SNS
