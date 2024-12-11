//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/model/ObjectCounter.h>

namespace AwsMock::Dto::S3 {

    std::string ObjectCounter::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "oid", oid);
            Core::Bson::BsonUtils::SetStringValue(document, "bucketName", bucketName);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            Core::Bson::BsonUtils::SetStringValue(document, "contentType", contentType);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ObjectCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ObjectCounter &c) {
        os << "ObjectCounter=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
