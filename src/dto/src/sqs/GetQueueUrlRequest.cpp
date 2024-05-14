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
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetQueueUrlRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("QueueName", queueName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    [[nodiscard]] std::string GetQueueUrlRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueUrlRequest &r) {
        os << "GetQueueUrlRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
