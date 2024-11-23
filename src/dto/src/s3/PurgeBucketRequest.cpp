//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/PurgeBucketRequest.h>

namespace AwsMock::Dto::S3 {

    PurgeBucketRequest PurgeBucketRequest::FromJson(const std::string &jsonString) {

        PurgeBucketRequest request;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("region", rootObject, request.region);
            Core::JsonUtils::GetJsonValueString("bucketName", rootObject, request.bucketName);

            return request;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string PurgeBucketRequest::ToJson() const {

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

    std::string PurgeBucketRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PurgeBucketRequest &r) {
        os << "PurgeBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
