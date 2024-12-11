//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UploadPartCopyRequest.h>

namespace AwsMock::Dto::S3 {

    std::string UploadPartCopyRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "uploadId", uploadId);
            Core::Bson::BsonUtils::SetIntValue(document, "partNumber", partNumber);
            Core::Bson::BsonUtils::SetStringValue(document, "sourceBucket", sourceBucket);
            Core::Bson::BsonUtils::SetStringValue(document, "sourceKey", sourceKey);
            Core::Bson::BsonUtils::SetStringValue(document, "targetBucket", targetBucket);
            Core::Bson::BsonUtils::SetStringValue(document, "targetKey", targetKey);
            Core::Bson::BsonUtils::SetLongValue(document, "min", min);
            Core::Bson::BsonUtils::SetLongValue(document, "max", max);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UploadPartCopyRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UploadPartCopyRequest &r) {
        os << "UploadPartCopyRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
