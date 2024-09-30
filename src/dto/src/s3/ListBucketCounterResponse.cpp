
#include <awsmock/dto/s3/ListBucketCounterResponse.h>

namespace AwsMock::Dto::S3 {

    std::string ListBucketCounterResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("total", total);

            // Contents
            if (!bucketCounters.empty()) {

                Poco::JSON::Array jsonBucketArray;
                for (auto &bucket: bucketCounters) {
                    Poco::JSON::Object jsonObject;
                    jsonObject.set("bucketName", bucket.bucketName);
                    jsonObject.set("keys", bucket.keys);
                    jsonObject.set("size", bucket.size);
                    jsonBucketArray.add(jsonObject);
                }

                rootJson.set("bucketCounters", jsonBucketArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string ListBucketCounterResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListBucketCounterResponse &r) {
        os << "ListBucketCounterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3