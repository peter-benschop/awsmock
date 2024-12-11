//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UploadPartCopyResponse.h>

namespace AwsMock::Dto::S3 {

    std::string UploadPartCopyResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("CopyPartResult.ETag", eTag);
            root.add("CopyPartResult.ChecksumCRC32", checksumCRC32);
            root.add("CopyPartResult.ChecksumCRC32C", checksumCRC32C);
            root.add("CopyPartResult.ChecksumSHA1", checksumSHA1);
            root.add("CopyPartResult.ChecksumSHA256", checksumSHA256);
            root.add("CopyPartResult.LastModified", Core::DateTimeUtils::ToISO8601(lastModified));
            root.add("CopyPartResult.ETag", eTag);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UploadPartCopyResponse::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "ETag", eTag);
            Core::Bson::BsonUtils::SetDateValue(document, "LastModified", lastModified);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumCRC32", checksumCRC32);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumCRC32C", checksumCRC32C);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumSHA1", checksumSHA1);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumSHA256", checksumSHA256);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UploadPartCopyResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UploadPartCopyResponse &p) {
        os << "UploadPartCopyResponse=" << p.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3