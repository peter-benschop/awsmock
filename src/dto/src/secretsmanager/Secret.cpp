//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Secret.h>

namespace AwsMock::Dto::SecretsManager {

    Poco::JSON::Object Secret::ToJsonObject() const {

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
        }
    }

    std::string Secret::ToJson() const {

        std::ostringstream os;
        ToJsonObject().stringify(os);
        return os.str();
    }

    void Secret::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string Secret::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Secret &tags) {
        os << "Secret=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager