//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CompleteMultipartUploadRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "Key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "UploadId", uploadId);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumCRC32", checksumCrc32);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumCRC32C", checksumCrc32c);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumSHA1", checksumSha1);
            Core::Bson::BsonUtils::SetStringValue(document, "ChecksumSHA256", checksumSha256);
            Core::Bson::BsonUtils::SetStringValue(document, "ETag", eTag);
            Core::Bson::BsonUtils::SetIntValue(document, "PartNumber", partNumber);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CompleteMultipartUploadRequest::FromXml(const std::string &xmlString) {

        try {

            boost::property_tree::ptree pt;
            read_xml(xmlString, pt);
            checksumCrc32 = pt.get<std::string>("CompleteMultipartUpload.Part.ChecksumCRC32");
            checksumCrc32c = pt.get<std::string>("CompleteMultipartUpload.Part.ChecksumCRC32C");
            checksumSha1 = pt.get<std::string>("CompleteMultipartUpload.Part.ChecksumSHA1");
            checksumSha256 = pt.get<std::string>("CompleteMultipartUpload.Part.ChecksumSHA256");
            eTag = pt.get<std::string>("CompleteMultipartUpload.Part.ETag");
            partNumber = pt.get<int>("CompleteMultipartUpload.Part.PartNumber");

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CompleteMultipartUploadRequest::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("CompleteMultipartUpload.Part.ETag", eTag);
            root.add("CompleteMultipartUpload.Part.ChecksumCRC32", checksumCrc32);
            root.add("CompleteMultipartUpload.Part.ChecksumCRC32C", checksumCrc32c);
            root.add("CompleteMultipartUpload.Part.ChecksumSHA1", checksumSha1);
            root.add("CompleteMultipartUpload.Part.ChecksumSHA256", checksumSha256);
            root.add("CompleteMultipartUpload.Part.PartNumber", partNumber);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CompleteMultipartUploadRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadRequest &r) {
        os << "CompleteMultipartUploadRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
