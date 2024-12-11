//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueRequest.h>

namespace AwsMock::Dto::SQS {

    std::string CreateQueueRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueName", queueName);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    void CreateQueueRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueName = Core::Bson::BsonUtils::GetStringValue(document, "QueueName");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string CreateQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateQueueRequest &r) {
        os << "CreateQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
