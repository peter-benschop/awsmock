//
// Created by vogje01 on 4/9/24.
//

#include <awsmock/dto/secretsmanager/GetSecretValueRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string GetSecretValueRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretId", secretId);
            Core::Bson::BsonUtils::SetStringValue(document, "VersionId", versionId);
            Core::Bson::BsonUtils::SetStringValue(document, "VersionStage", versionStage);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void GetSecretValueRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            secretId = Core::Bson::BsonUtils::GetStringValue(document, "SecretId");
            versionId = Core::Bson::BsonUtils::GetStringValue(document, "VersionId");
            versionStage = Core::Bson::BsonUtils::GetStringValue(document, "VersionStage");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
