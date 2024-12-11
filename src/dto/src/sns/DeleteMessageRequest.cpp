//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/DeleteMessageRequest.h>

namespace AwsMock::Dto::SNS {

    void DeleteMessageRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");
            messageId = Core::Bson::BsonUtils::GetStringValue(document, "messageId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteMessageRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "messageId", messageId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string DeleteMessageRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r) {
        os << "DeleteMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
