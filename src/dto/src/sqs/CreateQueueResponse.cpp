//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string CreateQueueResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("QueueName", name);
            rootJson.set("QueueUrl", queueUrl);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void CreateQueueResponse::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }
    }

    void CreateQueueResponse::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/CreateQueueResponse/CreateQueueResult/QueueUrl");
        if (node) {
            queueUrl = node->innerText();
        } else {
            std::cerr << "Exception: Wrong create queue payload" << std::endl;
        }
    }

    std::string CreateQueueResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "CreateQueueResponse");

        // CreateQueueResult

        Poco::XML::AutoPtr<Poco::XML::Element> pListQueueResult = Core::XmlUtils::CreateNode(pDoc, pRoot, "CreateQueueResult");

        Core::XmlUtils::CreateTextNode(pDoc, pListQueueResult, "QueueUrl", queueUrl);

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = Core::XmlUtils::CreateNode(pDoc, pRoot, "ResponseMetadata");
        Core::XmlUtils::CreateTextNode(pDoc, pMetaData, "RequestId", Poco::UUIDGenerator().createRandom().toString());

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string CreateQueueResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateQueueResponse &r) {
        os << "CreateQueueResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
