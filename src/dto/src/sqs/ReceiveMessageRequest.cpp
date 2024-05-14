//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sqs/ReceiveMessageRequest.h>

namespace AwsMock::Dto::SQS {

    void ReceiveMessageRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueInt("MaxNumberOfMessages", rootObject, maxMessages);
            Core::JsonUtils::GetJsonValueInt("WaitTimeSeconds", rootObject, waitTimeSeconds);
            Core::JsonUtils::GetJsonValueInt("VisibilityTimeout", rootObject, visibilityTimeout);

            // Attributes
            Poco::JSON::Array::Ptr attributes = rootObject->getArray("AttributeNames");
            for (const auto &attribute: *attributes) {
                messageAttributeNames.emplace_back(attribute.convert<std::string>());
            }

            // Message attributes
            Poco::JSON::Array::Ptr messageAttributes = rootObject->getArray("MessageAttributeNames");
            for (const auto &messageAttribute: *messageAttributes) {
                messageAttributeNames.emplace_back(messageAttribute.convert<std::string>());
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string ReceiveMessageRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r) {
        os << "ReceiveMessageRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', queueName='" << r.queueName << "', maxMessages='" << r.maxMessages << "', visibilityTimeout='" << r.visibilityTimeout << "', waitTimeSeconds='"
           << r.waitTimeSeconds << "', resource='" << r.resource << "', requestId: '" << r.requestId << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
