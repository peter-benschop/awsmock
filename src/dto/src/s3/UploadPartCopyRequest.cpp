//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UploadPartCopyRequest.h>

namespace AwsMock::Dto::S3 {

    std::string UploadPartCopyRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("uploadId", uploadId);
            rootJson.set("partNumber", partNumber);
            rootJson.set("region", region);
            rootJson.set("sourceBucket", sourceBucket);
            rootJson.set("sourceKey", sourceKey);
            rootJson.set("targetBucket", targetBucket);
            rootJson.set("targetKey", targetKey);
            rootJson.set("min", min);
            rootJson.set("max", max);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UploadPartCopyRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UploadPartCopyRequest &r) {
        os << "UploadPartCopyRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
