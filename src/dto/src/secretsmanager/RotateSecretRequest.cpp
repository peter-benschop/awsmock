//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/RotateSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string RotateSecretRequest::ToJson() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("SecretId", secretId);
            rootJson.set("ClientRequestToken", clientRequestToken);
            rootJson.set("RotationLambdaARN", rotationLambdaARN);
            rootJson.set("RotateImmediately", rotateImmediately);
            rootJson.set("RotationRules", rotationRules.ToJsonObject());
            rootJson.set("RequestId", requestId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void RotateSecretRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("SecretId", rootObject, secretId);
            Core::JsonUtils::GetJsonValueString("ClientRequestToken", rootObject, clientRequestToken);
            Core::JsonUtils::GetJsonValueString("RotationLambdaARN", rootObject, rotationLambdaARN);
            Core::JsonUtils::GetJsonValueBool("RotateImmediately", rootObject, rotateImmediately);
            rotationRules.FromJsonObject(rootObject->getObject("RotationRules"));

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string RotateSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RotateSecretRequest &r) {
        os << "RotateSecretRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
