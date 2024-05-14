//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/UpdateSecretResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string UpdateSecretResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("ARN", arn);
            rootJson.set("VersionId", versionId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    void UpdateSecretResponse::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("Name", rootObject, name);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }
    }

    std::string UpdateSecretResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateSecretResponse &r) {
        os << "UpdateSecretResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
