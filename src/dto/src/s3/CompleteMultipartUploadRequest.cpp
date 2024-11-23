//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CompleteMultipartUploadRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("user", user);
            rootJson.set("uploadId", uploadId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CompleteMultipartUploadRequest::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
        region = node->innerText();
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
