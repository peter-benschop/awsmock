//
// Created by vogje01 on 02/10/2023.
//

#include <awsmock/dto/sqs/PurgeQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void PurgeQueueRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string PurgeQueueRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("QueueUrl", queueUrl);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string PurgeQueueRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r) {
        os << "PurgeQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
