//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DescribeSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string DescribeSecretRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("SecretId", secretId);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    void DescribeSecretRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("SecretId", rootObject, secretId);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeSecretRequest &r) {
        os << "DescribeSecretRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
