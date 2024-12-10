//
// Created by vogje01 on 02/10/2023.
//

#include <awsmock/dto/sqs/PurgeQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void PurgeQueueRequest::FromJson(const std::string &jsonString) {


        try {

            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PurgeQueueRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PurgeQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r) {
        os << "PurgeQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
