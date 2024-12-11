//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CopyObjectRequest::ToJson() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "sourceBucket", sourceBucket);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "sourceKey", sourceKey);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "targetBucket", targetBucket);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "targetKey", targetKey);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "user", user);

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

    std::string CopyObjectRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CopyObjectRequest &r) {
        os << "CopyObjectRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
