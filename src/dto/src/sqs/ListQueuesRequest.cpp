//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void ListQueuesRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            if (!rootObject->get("MaxResults").isEmpty()) {
                maxResults = rootObject->get("MaxResults").convert<int>();
            }
            if (!rootObject->get("NextToken").isEmpty()) {
                nextToken = rootObject->get("NextToken").convert<std::string>();
            }
            if (!rootObject->get("QueueNamePrefix").isEmpty()) {
                queueNamePrefix = rootObject->get("QueueNamePrefix").convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListQueuesRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("NextToken", nextToken);
            rootJson.set("MaxResults", maxResults);
            rootJson.set("QueueNamePrefix", queueNamePrefix);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListQueuesRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueuesRequest &r) {
        os << "ListQueuesRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
