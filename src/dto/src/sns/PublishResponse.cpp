//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/PublishResponse.h>

namespace AwsMock::Dto::SNS {

    std::string PublishResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "PublishResponse");

        // SendMessageResult
        Poco::XML::AutoPtr<Poco::XML::Element> pSendMessageResult = Core::XmlUtils::CreateNode(pDoc, pRoot, "PublishResult");

        // MessageID
        Core::XmlUtils::CreateTextNode(pDoc, pSendMessageResult, "MessageId", messageId);

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = Core::XmlUtils::CreateNode(pDoc, pRoot, "ResponseMetadata");

        // Request ID
        Core::XmlUtils::CreateTextNode(pDoc, pMetaData, "RequestId", requestId);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string PublishResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("messageId", messageId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string PublishResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PublishResponse &r) {
        os << "PublishResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
