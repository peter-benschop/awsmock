//
// Created by vogje01 on 4/9/24.
//

#include <awsmock/dto/secretsmanager/GetSecretValueRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string GetSecretValueRequest::ToJson() const {

        // TOdo:
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("SecretId", secretId);
            rootJson.set("VersionId", versionId);
            rootJson.set("VersionStage", versionStage);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }

    void GetSecretValueRequest::FromJson(const std::string &jsonString) {

        // TOdo:
        /*
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("SecretId", rootObject, secretId);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
    }

    std::string GetSecretValueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetSecretValueRequest &r) {
        os << "GetSecretValueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
