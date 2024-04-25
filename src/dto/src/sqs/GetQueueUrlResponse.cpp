//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>

namespace AwsMock::Dto::SQS {

    void GetQueueUrlResponse::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/GetQueueUrlResponse/GetQueueUrlResult/QueueUrl");
        if (node) {
            queueUrl = node->innerText();
        } else {
            std::cerr << "Exception: Wrong create queue payload" << std::endl;
        }
    }

    std::string GetQueueUrlResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetQueueUrlResponse");
        pDoc->appendChild(pRoot);

        // CreateQueueResult
        Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrlResult = pDoc->createElement("GetQueueUrlResult");
        pRoot->appendChild(pQueueUrlResult);

        Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrl = pDoc->createElement("QueueUrl");
        pQueueUrlResult->appendChild(pQueueUrl);
        Poco::XML::AutoPtr<Poco::XML::Text> pQueueUrlText = pDoc->createTextNode(queueUrl);
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
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION);
        writer.writeNode(output, pDoc);
        return output.str();
    }

    std::string GetQueueUrlResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("QueueUrl", queueUrl);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    void GetQueueUrlResponse::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string GetQueueUrlResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueUrlResponse &r) {
        os << "GetQueueUrlRequest={queueUrl='" << r.queueUrl << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
