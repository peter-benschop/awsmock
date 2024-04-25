//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/CreateKeyRequest.h>

namespace AwsMock::Dto::Kms {

    void CreateKeyRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            std::string tmpStr;
            Core::JsonUtils::GetJsonValueBool("BypassPolicyLockoutSafetyCheck", rootObject, bypassPolicyLockoutSafetyCheck);
            Core::JsonUtils::GetJsonValueString("CustomerMasterKeySpec", rootObject, tmpStr);
            customerMasterKeySpec = CustomerMasterKeySpecFromString(tmpStr);
            Core::JsonUtils::GetJsonValueString("CustomKeyStoreId", rootObject, customKeyStoreId);
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateKeyRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("BypassPolicyLockoutSafetyCheck", bypassPolicyLockoutSafetyCheck);
            rootJson.set("CustomerMasterKeySpec", CustomerMasterKeySpecToString(customerMasterKeySpec));
            rootJson.set("CustomKeyStoreId", customKeyStoreId);
            rootJson.set("Description", description);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateKeyRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateKeyRequest &r) {
        os << "CreateKeyRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Kms
