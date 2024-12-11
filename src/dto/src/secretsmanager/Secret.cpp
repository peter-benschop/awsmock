//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Secret.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> Secret::ToDocument() const {

        /* Todo:
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("ARN", arn);
            rootJson.set("Name", name);
            rootJson.set("Description", description);
            rootJson.set("KmsKeyId", kmsKeyId);
            rootJson.set("OwningService", owningService);
            rootJson.set("PrimaryRegion", primaryRegion);

            rootJson.set("CreatedDate", createdDate);
            rootJson.set("DeletedDate", deletedDate);
            rootJson.set("LastAccessedDate", lastAccessedDate);
            rootJson.set("LastChangedDate", lastChangedDate);
            rootJson.set("LastRotatedDate", lastRotatedDate);
            rootJson.set("NextRotatedDate", nextRotatedDate);

            rootJson.set("RotationEnabled", rotationEnabled);
            rootJson.set("RotationLambdaARN", rotationLambdaARN);

            rootJson.set("RotationRules", rotationRules.ToJsonObject());

            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    void Secret::FromDocument(const view_or_value<view, value> &document) {
        /* Todo:
        try {

            Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }*/
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