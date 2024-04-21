//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/Code.h>

namespace AwsMock::Dto::Lambda {

    /**
     * Convert from a JSON object.
     *
     * @param jsonObject json object
     */
    void Code::FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("S3Bucket", jsonObject, s3Bucket);
            Core::JsonUtils::GetJsonValueString("S3Key", jsonObject, s3Key);
            Core::JsonUtils::GetJsonValueString("S3ObjectVersion", jsonObject, s3ObjectVersion);
            Core::JsonUtils::GetJsonValueString("ImageUri", jsonObject, imageUri);
            Core::JsonUtils::GetJsonValueString("ZipFile", jsonObject, zipFile);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Code::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    Poco::JSON::Object Code::ToJsonObject() const {

        Poco::JSON::Object rootObject;
        try {
            rootObject.set("ZipFile", zipFile);
            rootObject.set("S3Bucket", s3Bucket);
            rootObject.set("S3Key", s3Key);
            rootObject.set("S3ObjectVersion", s3ObjectVersion);
            rootObject.set("ImageUri", imageUri);
            rootObject.set("ImageUri", imageUri);
            rootObject.set("Location", location);
            rootObject.set("RepositoryType", repositoryType);
            rootObject.set("ResolvedImageUri", resolvedImageUri);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
        return rootObject;
    }

    std::string Code::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Code &r) {
        os << "Code=" << r.ToJson();
        return os;
    }

} // namespace AwsMock::Dto::lambda
