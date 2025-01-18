//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteAttributeRequest.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteAttributeRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "MessageId", messageId);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteAttributeRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            messageId = Core::Bson::BsonUtils::GetStringValue(document, "MessageId");
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteAttributeRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteAttributeRequest &r) {
        os << "DeleteAttributeRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
