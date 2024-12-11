//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/PutObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string PutObjectResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "md5Sum", md5Sum);
            Core::Bson::BsonUtils::SetStringValue(document, "sha1sum", sha1Sum);
            Core::Bson::BsonUtils::SetStringValue(document, "sha256sum", sha256sum);
            Core::Bson::BsonUtils::SetStringValue(document, "versionId", versionId);
            Core::Bson::BsonUtils::SetLongValue(document, "contentLength", contentLength);

            // rootJson.set("metadata", Core::JsonUtils::GetJsonObject(metadata));

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutObjectResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutObjectResponse &r) {
        os << "PutObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3