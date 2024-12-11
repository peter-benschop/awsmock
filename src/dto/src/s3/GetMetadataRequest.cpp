//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetMetadataRequest.h>

namespace AwsMock::Dto::S3 {

    std::string GetMetadataRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetMetadataRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetMetadataRequest &r) {
        os << "GetMetadataRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
