//
// Created by vogje01 on 4/9/24.
//

#include <awsmock/dto/secretsmanager/GetSecretValueResponse.h>

namespace AwsMock::Dto::SecretsManager {

    std::string GetSecretValueResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "VersionId", versionId);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretString", secretString);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretBinary", secretBinary);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void GetSecretValueResponse::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "ARN");
            versionId = Core::Bson::BsonUtils::GetStringValue(document, "VersionId");
            secretString = Core::Bson::BsonUtils::GetStringValue(document, "SecretString");
            secretBinary = Core::Bson::BsonUtils::GetStringValue(document, "SecretBinary");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
