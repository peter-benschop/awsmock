//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ScheduleKeyDeletionResponse.h>

namespace AwsMock::Dto::KMS {

    std::string ScheduledKeyDeletionResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("KeyId", keyId);
            rootJson.set("KeyState", keyState);
            rootJson.set("DeletionDate", deletionDate);
            rootJson.set("PendingWindowInDays", pendingWindowInDays);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ScheduledKeyDeletionResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ScheduledKeyDeletionResponse &r) {
        os << "ScheduledKeyDeletionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
