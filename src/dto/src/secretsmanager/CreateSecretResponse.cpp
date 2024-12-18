//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/CreateSecretResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string CreateSecretResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "VersionId", versionId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateSecretResponse::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "ARN");
            versionId = Core::Bson::BsonUtils::GetStringValue(document, "VersionId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateSecretResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateSecretResponse &r) {
        os << "CreateSecretResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
