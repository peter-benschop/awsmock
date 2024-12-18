//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DeleteSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    void DeleteSecretRequest::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteSecretRequest &r) {
        os << "DeleteSecretRequest={region='" << r.region << "', name='" << r.name << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
