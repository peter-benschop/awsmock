//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/UpdateSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string UpdateSecretRequest::ToJson() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("SecretId", secretId);
            rootJson.set("Description", description);
            rootJson.set("SecretString", secretString);
            rootJson.set("SecretBinary", secretBinary);
            rootJson.set("KmsKeyId", kmsKeyId);
            rootJson.set("RequestId", requestId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void UpdateSecretRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("SecretId", rootObject, secretId);
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
            Core::JsonUtils::GetJsonValueString("SecretString", rootObject, secretString);
            Core::JsonUtils::GetJsonValueString("SecretBinary", rootObject, secretBinary);
            Core::JsonUtils::GetJsonValueString("KmsKeyId", rootObject, kmsKeyId);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string UpdateSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateSecretRequest &r) {
        os << "UpdateSecretRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
