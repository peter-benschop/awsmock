//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/s3/ListObjectVersionsRequest.h>

namespace AwsMock::Dto::S3 {

    std::string ListObjectVersionsRequest::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "prefix", prefix);
            Core::Bson::BsonUtils::SetStringValue(document, "delimiter", delimiter);
            Core::Bson::BsonUtils::SetStringValue(document, "encodingType", encodingType);
            Core::Bson::BsonUtils::SetIntValue(document, "maxKeys", maxKeys);
            Core::Bson::BsonUtils::SetStringValue(document, "versionIdMarker", versionIdMarker);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListObjectVersionsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListObjectVersionsRequest &r) {
        os << "ListObjectVersionsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
