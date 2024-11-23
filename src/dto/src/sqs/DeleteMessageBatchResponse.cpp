
#include <awsmock/dto/sqs/DeleteMessageBatchResponse.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;

            if (!failed.empty()) {
                Poco::JSON::Array jsonFailedArray;
                for (const auto &f: failed) {
                    jsonFailedArray.add(f.ToJsonObject());
                }
                rootJson.set("Failed", jsonFailedArray);
            }

            if (!successFull.empty()) {
                Poco::JSON::Array jsonSuccessfulArray;
                for (const auto &f: successFull) {
                    jsonSuccessfulArray.add(f.ToJsonObject());
                }
                rootJson.set("Successful", jsonSuccessfulArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    [[nodiscard]] std::string DeleteMessageBatchResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "DeleteMessageBatchResponse");

        // Result
        Poco::XML::AutoPtr<Poco::XML::Element> pResult = Core::XmlUtils::CreateNode(pDoc, pRoot, "DeleteMessageBatchResult");

        // Successful
        for (const auto &f: failed) {
            Poco::XML::AutoPtr<Poco::XML::Element> pResultEntry = Core::XmlUtils::CreateNode(pDoc, pRoot, "DeleteMessageBatchResultEntry");
            Core::XmlUtils::CreateTextNode(pDoc, pResultEntry, "Id", f.id);
            Core::XmlUtils::CreateTextNode(pDoc, pResultEntry, "Code", f.code);
            Core::XmlUtils::CreateTextNode(pDoc, pResultEntry, "SenderFault", f.senderFault);
            Core::XmlUtils::CreateTextNode(pDoc, pResultEntry, "Message", f.message);
        }

        // Failed
        for (const auto &f: successFull) {
            Poco::XML::AutoPtr<Poco::XML::Element> pResultEntry = Core::XmlUtils::CreateNode(pDoc, pRoot, "DeleteMessageBatchResultEntry");
            Core::XmlUtils::CreateTextNode(pDoc, pResultEntry, "Id", f.id);
        }

        // Metadata
        Poco::XML::AutoPtr<Poco::XML::Element> pMetadata = Core::XmlUtils::CreateNode(pDoc, pRoot, "ResponseMetadata");
        Core::XmlUtils::CreateTextNode(pDoc, pMetadata, "RequestId", requestId);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    [[nodiscard]] std::string DeleteMessageBatchResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchResponse &r) {
        os << "DeleteMessageBatchResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
