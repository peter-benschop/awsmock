//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchEntry.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchEntry::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "ReceiptHandle", receiptHandle);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> DeleteMessageBatchEntry::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "ReceiptHandle", receiptHandle);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteMessageBatchEntry::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d) {
        os << "DeleteMessageBatchEntry=" << d.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
