//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/GetQueueDetailsRequest.h>

namespace AwsMock::Dto::SQS {

    void GetQueueDetailsRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueArn", rootObject, queueArn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetQueueDetailsRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("QueueArn", queueArn);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    [[nodiscard]] std::string GetQueueDetailsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueDetailsRequest &r) {
        os << "GetQueueDetailsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
