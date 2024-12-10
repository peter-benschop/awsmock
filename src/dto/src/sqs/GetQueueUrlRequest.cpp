//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/GetQueueUrlRequest.h>

namespace AwsMock::Dto::SQS {

    void GetQueueUrlRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            queueName = Core::Bson::BsonUtils::GetStringValue(document, "QueueName");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueUrlRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueName", queueName);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string GetQueueUrlRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueUrlRequest &r) {
        os << "GetQueueUrlRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
