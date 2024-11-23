//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueuesResponse::ToXml() const {

        try {

            // Root
            Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
            Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "ListQueuesResponse");

            // ListQueuesResult
            Poco::XML::AutoPtr<Poco::XML::Element> pListQueueResult = Core::XmlUtils::CreateNode(pDoc, pRoot, "ListQueuesResult");

            for (auto &it: queueList) {
                Core::XmlUtils::CreateTextNode(pDoc, pListQueueResult, "QueueUrl", it.queueUrl);
            }

            // Metadata
            Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = Core::XmlUtils::CreateNode(pDoc, pRoot, "ResponseMetadata");
            Core::XmlUtils::CreateTextNode(pDoc, pListQueueResult, "RequestId", Poco::UUIDGenerator().createRandom().toString());
            return Core::XmlUtils::ToXmlString(pDoc);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListQueuesResponse::ToJson() const {

        try {
            Poco::JSON::Array queuesArrayJson;
            for (const auto &queue: queueList) {
                queuesArrayJson.add(queue.queueUrl);
            }

            Poco::JSON::Object rootJson;
            rootJson.set("QueueUrls", queuesArrayJson);
            rootJson.set("NextToken", nextToken);
            rootJson.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListQueuesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueuesResponse &r) {
        os << "ListQueuesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
