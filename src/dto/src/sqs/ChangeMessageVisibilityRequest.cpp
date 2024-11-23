//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/ChangeMessageVisibilityRequest.h>

namespace AwsMock::Dto::SQS {

    std::string ChangeMessageVisibilityRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("QueueUrl", queueUrl);
            rootJson.set("ReceiptHandle", receiptHandle);
            rootJson.set("VisibilityTimeout", visibilityTimeout);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void ChangeMessageVisibilityRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueString("ReceiptHandle", rootObject, receiptHandle);
            Core::JsonUtils::GetJsonValueInt("VisibilityTimeout", rootObject, visibilityTimeout);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ChangeMessageVisibilityRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ChangeMessageVisibilityRequest &r) {
        os << "ChangeMessageVisibilityRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
