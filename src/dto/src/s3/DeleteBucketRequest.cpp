//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteBucketRequest.h>

namespace AwsMock::Dto::S3 {

    std::string DeleteBucketRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("owner", owner);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteBucketRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteBucketRequest &r) {
        os << "DeleteBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
