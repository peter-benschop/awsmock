//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void ListQueuesRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            maxResults = Core::Bson::BsonUtils::GetIntValue(document, "maxResults");
            nextToken = Core::Bson::BsonUtils::GetStringValue(document, "NextToken");
            queueNamePrefix = Core::Bson::BsonUtils::GetStringValue(document, "QueueNamePrefix");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ListQueuesRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);
            Core::Bson::BsonUtils::SetIntValue(document, "MaxResults", maxResults);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueNamePrefix", queueNamePrefix);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ListQueuesRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueuesRequest &r) {
        os << "ListQueuesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
