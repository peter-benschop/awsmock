//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/GetQueueUrlRequest.h>

namespace AwsMock::Dto::SQS {

    void GetQueueUrlRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueName", rootObject, queueName);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    [[nodiscard]] std::string GetQueueUrlRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueUrlRequest &r) {
        os << "GetQueueUrlRequest={region='" << r.region << "' queueName='" << r.queueName << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
