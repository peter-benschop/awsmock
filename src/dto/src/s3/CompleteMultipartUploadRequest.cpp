//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CompleteMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CompleteMultipartUploadRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "user", user);
            Core::Bson::BsonUtils::SetStringValue(document, "uploadId", uploadId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CompleteMultipartUploadRequest::FromXml(const std::string &xmlString) {

        /* Todo:
        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
        region = node->innerText();*/
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
