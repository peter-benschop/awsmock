//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/UploadPartCopyResponse.h>

namespace AwsMock::Dto::S3 {

    std::string UploadPartCopyResponse::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CopyPartResult");
        pDoc->appendChild(pRoot);

        // ETag
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ETag", eTag);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "LastModified", Core::DateTimeUtils::ToISO8601(lastModified));

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string UploadPartCopyResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("ETag", eTag);
            rootJson.set("LastModified", Core::DateTimeUtils::ToISO8601(lastModified));
            rootJson.set("ChecksumCRC32", checksumCRC32);
            rootJson.set("ChecksumCRC32C", checksumCRC32C);
            rootJson.set("ChecksumSHA1", checksumSHA1);
            rootJson.set("ChecksumSHA256", checksumSHA256);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UploadPartCopyResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UploadPartCopyResponse &r) {
        os << "UploadPartCopyResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3