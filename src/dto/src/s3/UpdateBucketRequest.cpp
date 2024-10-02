//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UpdateBucketRequest.h>

namespace AwsMock::Dto::S3 {

    UpdateBucketRequest UpdateBucketRequest::FromJson(const std::string &jsonString) {

        UpdateBucketRequest request;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            if (!rootObject->get("bucket").isEmpty()) {
                Bucket bucket;
                bucket.FromJsonObject(rootObject->getObject("bucket"));
            }
            return request;
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateBucketRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("bucket", bucket.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UpdateBucketRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateBucketRequest &r) {
        os << "UpdateBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
