//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ScheduleKeyDeletionResponse.h>

namespace AwsMock::Dto::KMS {

    std::string ScheduledKeyDeletionResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "KeyId", keyId);
            Core::Bson::BsonUtils::SetStringValue(document, "KeyState", keyState);
            Core::Bson::BsonUtils::SetLongValue(document, "DeletionDate", deletionDate);
            Core::Bson::BsonUtils::SetIntValue(document, "PendingWindowInDays", pendingWindowInDays);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ScheduledKeyDeletionResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ScheduledKeyDeletionResponse &r) {
        os << "ScheduledKeyDeletionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
