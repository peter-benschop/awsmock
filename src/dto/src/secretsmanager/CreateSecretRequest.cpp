//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/CreateSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string CreateSecretRequest::ToJson() const {


        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "ClientRequestToken", clientRequestToken);
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretString", secretString);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretBinary", secretBinary);
            Core::Bson::BsonUtils::SetBoolValue(document, "ForceOverwriteReplicaSecret", forceOverwriteReplicaSecret);
            Core::Bson::BsonUtils::SetStringValue(document, "KmsKeyId", kmsKeyId);
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);

            // Tags
            document.append(kvp("Tags", tags.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateSecretRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "FunctionName");
            clientRequestToken = Core::Bson::BsonUtils::GetStringValue(document, "ClientRequestToken");
            description = Core::Bson::BsonUtils::GetStringValue(document, "Description");
            secretString = Core::Bson::BsonUtils::GetStringValue(document, "SecretString");
            secretBinary = Core::Bson::BsonUtils::GetStringValue(document, "SecretBinary");
            forceOverwriteReplicaSecret = Core::Bson::BsonUtils::GetBoolValue(document, "ForceOverwriteReplicaSecret");
            kmsKeyId = Core::Bson::BsonUtils::GetStringValue(document, "KmsKeyId");

            // Tags
            if (document.view().find("Tags") != document.view().end()) {
                tags.FromDocument(document.view()["Tags"].get_document().value);
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateSecretRequest &r) {
        os << "CreateQueueRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
