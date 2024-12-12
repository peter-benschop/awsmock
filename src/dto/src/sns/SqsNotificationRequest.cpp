//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/SqsNotificationRequest.h>

namespace AwsMock::Dto::SNS {

    std::string SqsNotificationRequest::ToJson() const {


        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Type", type);
            Core::Bson::BsonUtils::SetStringValue(document, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(document, "TopicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(document, "Message", message);
            Core::Bson::BsonUtils::SetLongValue(document, "Timestamp", timestamp);
            Core::Bson::BsonUtils::SetStringValue(document, "SignatureVersion", signatureVersion);
            Core::Bson::BsonUtils::SetStringValue(document, "Signature", signature);
            Core::Bson::BsonUtils::SetStringValue(document, "SignatureCertURL", signingCertURL);
            Core::Bson::BsonUtils::SetStringValue(document, "UnsubscribeURL", unsubscribeURL);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SqsNotificationRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SqsNotificationRequest &r) {
        os << "SqsNotificationRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
