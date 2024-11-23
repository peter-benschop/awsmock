//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetBucketRequest.h>

namespace AwsMock::Dto::S3 {

    GetBucketRequest GetBucketRequest::FromJson(const std::string &jsonString) {

        GetBucketRequest request;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            if (!rootObject->get("region").isEmpty()) {
                request.region = rootObject->get("region").convert<std::string>();
            }
            if (!rootObject->get("bucketName").isEmpty()) {
                request.bucketName = rootObject->get("bucketName").convert<std::string>();
            }
            return request;
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetBucketRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucketName", bucketName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetBucketRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetBucketRequest &r) {
        os << "GetBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
