//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/ListSecretsResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string ListSecretsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("NextToken", nextToken);

            Poco::JSON::Array jsonSecretsArray;
            for (const auto &secret: secretList) {
                jsonSecretsArray.add(secret.ToJsonObject());
            }
            rootJson.set("SecretList", jsonSecretsArray);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListSecretsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSecretsResponse &r) {
        os << "ListSecretsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
