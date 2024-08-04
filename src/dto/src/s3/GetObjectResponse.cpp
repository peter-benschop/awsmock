//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string GetObjectResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("size", size);
            rootJson.set("filename", filename);
            rootJson.set("contentType", contentType);
            rootJson.set("md5sum", md5sum);
            rootJson.set("metadata", Core::JsonUtils::GetJsonObject(metadata));
            rootJson.set("created", Core::DateTimeUtils::ISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ISO8601(modified));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetObjectResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r) {
        os << "GetObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
