//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteQueueResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteQueueResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("DeleteQueueResponse.ResponseMetadata.RequestId", requestId);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteQueueResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteQueueResponse &r) {
        os << "DeleteQueueResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
