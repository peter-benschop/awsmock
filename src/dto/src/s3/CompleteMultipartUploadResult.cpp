//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

    std::string CompleteMultipartUploadResult::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("location", location);
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("etag", etag);
            rootJson.set("checksumCrc32", checksumCrc32);
            rootJson.set("checksumCrc32c", checksumCrc32c);
            rootJson.set("checksumSha1", checksumSha1);
            rootJson.set("checksumSha256", checksumSha256);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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
