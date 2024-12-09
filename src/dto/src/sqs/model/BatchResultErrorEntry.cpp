//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/BatchResultErrorEntry.h>
#include <jwt-cpp/jwt.h>

namespace AwsMock::Dto::SQS {

    std::string BatchResultErrorEntry::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> BatchResultErrorEntry::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Code", code);
            Core::Bson::BsonUtils::SetStringValue(document, "Message", message);
            Core::Bson::BsonUtils::SetBoolValue(document, "SenderFault", senderFault);

            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string BatchResultErrorEntry::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const BatchResultErrorEntry &r) {
        os << "BatchResultErrorEntry=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
