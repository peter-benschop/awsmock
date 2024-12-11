//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/ScheduleKeyDeletionRequest.h>

namespace AwsMock::Dto::KMS {

    void ScheduleKeyDeletionRequest::FromJson(const std::string &jsonString) {

        /* Todo:
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);
            Core::JsonUtils::GetJsonValueInt("PendingWindowInDays", rootObject, pendingWindowInDays);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string ScheduleKeyDeletionRequest::ToJson() const {

        /* Todo:
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("KeyId", keyId);
            rootJson.set("PendingWindowInDays", pendingWindowInDays);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string ScheduleKeyDeletionRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ScheduleKeyDeletionRequest &r) {
        os << "ScheduleKeyDeletionRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
