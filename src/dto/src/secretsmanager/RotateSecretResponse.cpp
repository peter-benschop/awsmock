//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/RotateSecretResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string RotateSecretResponse::ToJson() const {

        /* Todo
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ARN", arn);
            rootJson.set("VersionId", versionId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
        */
        return {};
    }

    void RotateSecretResponse::FromJson(const std::string &jsonString) {

        /* Todo
        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ARN", rootObject, arn);
            Core::JsonUtils::GetJsonValueString("VersionId", rootObject, versionId);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }*/
    }

    std::string RotateSecretResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RotateSecretResponse &r) {
        os << "RotateSecretResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
