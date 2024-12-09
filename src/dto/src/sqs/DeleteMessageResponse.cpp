
#include <awsmock/dto/sqs/DeleteMessageResponse.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageResponse::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);
            Core::Bson::BsonUtils::SetStringValue(document, "Resource", resource);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string DeleteMessageResponse::ToXml() const {

        // Root
        boost::property_tree::ptree pt;
        pt.put("DeleteMessageResponse.ResponseMetadata.RequestId", requestId);
        pt.put("DeleteMessageResponse.ResponseMetadata.Resource", resource);
        return Core::XmlUtils::ToXmlString(pt);
    }

    [[nodiscard]] std::string DeleteMessageResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageResponse &r) {
        os << "DeleteMessageResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
