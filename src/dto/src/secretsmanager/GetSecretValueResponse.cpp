//
// Created by vogje01 on 4/9/24.
//

#include <awsmock/dto/secretsmanager/GetSecretValueResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string GetSecretValueResponse::ToJson() const {

        /* Todo:
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("ARN", arn);
            rootJson.set("versionId", versionId);
            if (!secretString.empty()) {
                rootJson.set("SecretString", secretString);
            } else {
                rootJson.set("SecretBinary", secretBinary);
            }

            // Stages
            Poco::JSON::Array stagesArray;
            for (const auto &s: versionStages) {
                stagesArray.add(s);
            }
            rootJson.set("VersionStages", versionStages);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }

    void GetSecretValueResponse::FromJson(const std::string &jsonString) {

        /* Todo:
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", rootObject, name);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
    }

    std::string GetSecretValueResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetSecretValueResponse &r) {
        os << "GetSecretValueResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
