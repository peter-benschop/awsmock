//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteBucketRequest.h>

namespace AwsMock::Dto::S3 {

    std::string DeleteBucketRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "owner", owner);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
