//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetMetadataResponse.h>

namespace AwsMock::Dto::S3 {

    std::string GetMetadataResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "key", key);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "md5sum", md5Sum);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "contentType", contentType);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "size", size);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "contentType", contentType);

            document metadataDocument;
            for (const auto &[fst, snd]: metadata) {
                Core::Bson::BsonUtils::SetStringValue(metadataDocument, fst, snd);
            }
            rootDocument.append(kvp("metadata", metadataDocument));

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetMetadataResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetMetadataResponse &r) {
        os << "GetMetadataResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
