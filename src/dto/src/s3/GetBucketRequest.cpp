//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetBucketRequest.h>

namespace AwsMock::Dto::S3 {

    GetBucketRequest GetBucketRequest::FromJson(const std::string &jsonString) {


        try {
            GetBucketRequest request;
            const value document = bsoncxx::from_json(jsonString);
            request.region = Core::Bson::BsonUtils::GetStringValue(document, "region");
            request.bucketName = Core::Bson::BsonUtils::GetStringValue(document, "bucketName");
            return request;

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetBucketRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucketName", bucketName);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
