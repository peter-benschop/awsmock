//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/CreateKeyRequest.h>

namespace AwsMock::Dto::KMS {

    void CreateKeyRequest::FromJson(const std::string &jsonString) {

        /* Todo:
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            std::string tmpStr;
            Core::JsonUtils::GetJsonValueBool("BypassPolicyLockoutSafetyCheck", rootObject, bypassPolicyLockoutSafetyCheck);
            Core::JsonUtils::GetJsonValueString("KeySpec", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                keySpec = KeySpecFromString(tmpStr);
            }
            Core::JsonUtils::GetJsonValueString("KeyUsage", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                keyUsage = KeyUsageFromString(tmpStr);
            }
            Core::JsonUtils::GetJsonValueString("CustomKeyStoreId", rootObject, customKeyStoreId);
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
            Core::JsonUtils::GetJsonValueString("Origin", rootObject, origin);
            Core::JsonUtils::GetJsonValueString("Policy", rootObject, policy);
            Core::JsonUtils::GetJsonValueString("XksKeyId", rootObject, xksKeyId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string CreateKeyRequest::ToJson() const {

        /* Todo
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("BypassPolicyLockoutSafetyCheck", bypassPolicyLockoutSafetyCheck);
            rootJson.set("KeySpec", KeySpecToString(keySpec));
            rootJson.set("KeyUsage", KeyUsageToString(keyUsage));
            rootJson.set("CustomKeyStoreId", customKeyStoreId);
            rootJson.set("Description", description);
            rootJson.set("Origin", origin);
            rootJson.set("Policy", policy);
            rootJson.set("XksKeyId", xksKeyId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string CreateKeyRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateKeyRequest &r) {
        os << "CreateKeyRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
