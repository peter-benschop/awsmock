//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesResponse.h>

namespace AwsMock::Dto::SQS {

    std::string SetQueueAttributesResponse::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "requestId", requestId);
            Core::Bson::BsonUtils::SetStringValue(document, "resource", resource);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string SetQueueAttributesResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("SetQueueAttributesResponse.ResponseMetadata.RequestId", requestId);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string SetQueueAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SetQueueAttributesResponse &r) {
        os << "SetQueueAttributesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
