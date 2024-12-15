//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

    std::string CompleteMultipartUploadResult::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "location", location);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "etag", etag);
            Core::Bson::BsonUtils::SetStringValue(document, "checksumCrc32", checksumCrc32);
            Core::Bson::BsonUtils::SetStringValue(document, "checksumCrc32c", checksumCrc32);
            Core::Bson::BsonUtils::SetStringValue(document, "checksumSha1", checksumSha1);
            Core::Bson::BsonUtils::SetStringValue(document, "checksumSha256", checksumSha256);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CompleteMultipartUploadResult::ToXml() const {

        boost::property_tree::ptree root;
        root.add("CompleteMultipartUploadResult.Location", location);
        root.add("CompleteMultipartUploadResult.Bucket", bucket);
        root.add("CompleteMultipartUploadResult.Key", key);
        root.add("CompleteMultipartUploadResult.ETag", etag);
        root.add("CompleteMultipartUploadResult.ChecksumCRC32", checksumCrc32);
        root.add("CompleteMultipartUploadResult.ChecksumCRC32C", checksumCrc32c);
        root.add("CompleteMultipartUploadResult.ChecksumSHA1", checksumSha1);
        root.add("CompleteMultipartUploadResult.ChecksumSHA256", checksumSha256);

        return Core::XmlUtils::ToXmlString(root);
    }

    std::string CompleteMultipartUploadResult::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadResult &r) {
        os << "CompleteMultipartUploadResult=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
