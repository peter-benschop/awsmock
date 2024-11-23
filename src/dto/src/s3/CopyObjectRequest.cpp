//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CopyObjectRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("sourceBucket", sourceBucket);
            rootJson.set("sourceKey", sourceKey);
            rootJson.set("targetBucket", targetBucket);
            rootJson.set("targetKey", targetKey);
            rootJson.set("metadata", Core::JsonUtils::GetJsonObject(metadata));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CopyObjectRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CopyObjectRequest &r) {
        os << "CopyObjectRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
