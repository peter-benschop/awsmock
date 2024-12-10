//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageRequest.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            Core::Bson::BsonUtils::SetStringValue(document, "ReceiptHandle", receiptHandle);
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteMessageRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");
            receiptHandle = Core::Bson::BsonUtils::GetStringValue(document, "ReceiptHandle");
            requestId = Core::Bson::BsonUtils::GetStringValue(document, "RequestId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteMessageRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r) {
        os << "DeleteMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
