//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueRequest.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteQueueRequest::ToJson() const {

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

    void DeleteQueueRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteQueueRequest &r) {
        os << "DeleteQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
