//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Secret.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> Secret::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetStringValue(document, "KmsKeyId", kmsKeyId);
            Core::Bson::BsonUtils::SetStringValue(document, "OwningService", owningService);
            Core::Bson::BsonUtils::SetStringValue(document, "PrimaryRegion", primaryRegion);
            Core::Bson::BsonUtils::SetLongValue(document, "CreatedDate", createdDate);
            Core::Bson::BsonUtils::SetLongValue(document, "DeletedDate", deletedDate);
            Core::Bson::BsonUtils::SetLongValue(document, "LastAccessedDate", lastAccessedDate);
            Core::Bson::BsonUtils::SetLongValue(document, "LastChangedDate", lastChangedDate);
            Core::Bson::BsonUtils::SetLongValue(document, "LastRotatedDate", lastRotatedDate);
            Core::Bson::BsonUtils::SetLongValue(document, "NextRotatedDate", nextRotatedDate);
            Core::Bson::BsonUtils::SetBoolValue(document, "RotationEnabled", rotationEnabled);
            Core::Bson::BsonUtils::SetStringValue(document, "RotationLambdaARN", rotationLambdaARN);

            document.append(kvp("RotationRules", rotationRules.ToDocument()));

            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Secret::FromDocument(const view_or_value<view, value> &document) {

        try {

            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "ARN");
            description = Core::Bson::BsonUtils::GetStringValue(document, "Description");
            kmsKeyId = Core::Bson::BsonUtils::GetStringValue(document, "KmsKeyId");
            owningService = Core::Bson::BsonUtils::GetStringValue(document, "OwningService");
            primaryRegion = Core::Bson::BsonUtils::GetStringValue(document, "PrimaryRegion");
            createdDate = Core::Bson::BsonUtils::GetLongValue(document, "CreatedDate");
            deletedDate = Core::Bson::BsonUtils::GetLongValue(document, "DeletedDate");
            lastAccessedDate = Core::Bson::BsonUtils::GetLongValue(document, "LastAccessedDate");
            lastChangedDate = Core::Bson::BsonUtils::GetLongValue(document, "LastChangedDate");
            lastRotatedDate = Core::Bson::BsonUtils::GetLongValue(document, "LastRotatedDate");
            nextRotatedDate = Core::Bson::BsonUtils::GetLongValue(document, "NextRotatedDate");
            rotationEnabled = Core::Bson::BsonUtils::GetBoolValue(document, "RotationEnabled");
            rotationLambdaARN = Core::Bson::BsonUtils::GetStringValue(document, "RotationLambdaARN");

            if (document.view().find("RotationRules") != document.view().end()) {
                rotationRules.FromDocument(document.view()["RotationRules"].get_document().value);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Secret::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Secret::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Secret &tags) {
        os << "Secret=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager