//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueRequest.h>

namespace AwsMock::Dto::SQS {

    std::string CreateQueueRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("QueueName", queueName);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void CreateQueueRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueName", rootObject, queueName);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
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
