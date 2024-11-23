//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/Content.h>

namespace AwsMock::Dto::S3 {

    std::string Content::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("etag", etag);
            rootJson.set("key", key);
            rootJson.set("owner", owner);
            rootJson.set("size", size);
            rootJson.set("storageClass", storageClass);
            rootJson.set("modified", lastModified);
            rootJson.set("checksumAlgorithms", Core::JsonUtils::GetJsonStringArray(checksumAlgorithms));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Content::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Content &c) {
        os << "Content=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
