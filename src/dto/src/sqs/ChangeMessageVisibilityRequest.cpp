//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/ChangeMessageVisibilityRequest.h>

namespace AwsMock::Dto::SQS {

    std::string ChangeMessageVisibilityRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            Core::Bson::BsonUtils::SetStringValue(document, "ReceiptHandle", receiptHandle);
            Core::Bson::BsonUtils::SetIntValue(document, "VisibilityTimeout", visibilityTimeout);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    void ChangeMessageVisibilityRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");
            receiptHandle = Core::Bson::BsonUtils::GetStringValue(document, "ReceiptHandle");
            visibilityTimeout = Core::Bson::BsonUtils::GetIntValue(document, "VisibilityTimeout");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ChangeMessageVisibilityRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ChangeMessageVisibilityRequest &r) {
        os << "ChangeMessageVisibilityRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
