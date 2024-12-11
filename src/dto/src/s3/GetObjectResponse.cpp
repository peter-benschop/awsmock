//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string GetObjectResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "key", key);
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "size", size);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "filename", filename);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "contentType", contentType);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "md5sum", md5sum);
            Core::Bson::BsonUtils::SetDateValue(rootDocument, "created", created);
            Core::Bson::BsonUtils::SetDateValue(rootDocument, "modified", modified);

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

    std::string GetObjectResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r) {
        os << "GetObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
