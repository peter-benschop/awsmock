//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/BucketCounter.h>

namespace AwsMock::Dto::S3 {

    std::string BucketCounter::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "bucketName", bucketName);
            Core::Bson::BsonUtils::SetLongValue(document, "keys", keys);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string BucketCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const BucketCounter &c) {
        os << "BucketCounter=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
