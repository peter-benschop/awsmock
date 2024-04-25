//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CreateMultipartUploadRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("user", user);
            rootJson.set("uploadId", uploadId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    void CreateMultipartUploadRequest::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
        region = node->innerText();
    }

    std::string CreateMultipartUploadRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadRequest &r) {
        os << "CreateMultipartUploadRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
