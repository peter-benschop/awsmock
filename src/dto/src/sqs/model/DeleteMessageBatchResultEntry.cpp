//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/DeleteMessageBatchResultEntry.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchResultEntry::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> DeleteMessageBatchResultEntry::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string DeleteMessageBatchResultEntry::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchResultEntry &r) {
        os << "DeleteMessageBatchResultEntry=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
