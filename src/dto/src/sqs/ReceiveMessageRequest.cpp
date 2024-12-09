//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sqs/ReceiveMessageRequest.h>

namespace AwsMock::Dto::SQS {

    void ReceiveMessageRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");
            waitTimeSeconds = Core::Bson::BsonUtils::GetIntValue(document, "WaitTimeSeconds");
            maxMessages = Core::Bson::BsonUtils::GetIntValue(document, "MaxNumberOfMessages");
            visibilityTimeout = Core::Bson::BsonUtils::GetIntValue(document, "VisibilityTimeout");

            // Attributes
            if (document.find("AttributeNames") != document.end()) {
                Core::Bson::FromBsonStringArray(document, "AttributeNames", &messageAttributeNames);
            }

            // Message attributes
            if (document.find("MessageAttributeNames") != document.end()) {
                Core::Bson::FromBsonStringArray(document, "MessageAttributeNames", &messageAttributeNames);
            }

            // Sanitize
            queueUrl = Core::SanitizeSQSUrl(queueUrl);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ReceiveMessageRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);
            Core::Bson::BsonUtils::SetIntValue(document, "MaxNumberOfMessages", maxMessages);
            Core::Bson::BsonUtils::SetIntValue(document, "WaitTimeSeconds", waitTimeSeconds);
            Core::Bson::BsonUtils::SetIntValue(document, "VisibilityTimeout", visibilityTimeout);

            if (!attributeNames.empty()) {
                array jsonArray;
                for (const auto &attributeName: attributeNames) {
                    jsonArray.append(attributeName);
                }
                document.append(kvp("Attributes", jsonArray));
            }

            if (!messageAttributeNames.empty()) {
                array jsonArray;
                for (const auto &attributeName: messageAttributeNames) {
                    jsonArray.append(attributeName);
                }
                document.append(kvp("Attributes", jsonArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ReceiveMessageRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r) {
        os << "ReceiveMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
