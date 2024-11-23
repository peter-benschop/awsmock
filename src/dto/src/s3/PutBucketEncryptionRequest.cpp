//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketEncryptionRequest.h>

namespace AwsMock::Dto::S3 {

    void PutBucketEncryptionRequest::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *rootNode = pDoc->getNodeByPath("/ServerSideEncryptionConfiguration");
        if (rootNode) {

            Poco::XML::Node *ruleNode = rootNode->firstChild();
            Poco::XML::Node *sseEncryptionConfiguration = ruleNode->firstChild();

            if (sseEncryptionConfiguration) {
                for (int i = 0; i < sseEncryptionConfiguration->childNodes()->length(); i++) {
                    Poco::XML::Node *childNode = sseEncryptionConfiguration->childNodes()->item(i);
                    if (childNode->nodeName() == "SSEAlgorithm") {
                        sseAlgorithm = childNode->lastChild()->innerText();
                    } else if (childNode->nodeName() == "KMSKeyID" || childNode->nodeName() == "KMSMasterKeyID") {
                        kmsKeyId = childNode->lastChild()->innerText();
                    }
                }
            }
        }
    }

    std::string PutBucketEncryptionRequest::ToJson() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("bucket", bucket);
        jsonObject.set("sseAlgorithm", sseAlgorithm);
        jsonObject.set("kmsKeyId", kmsKeyId);
        return Core::JsonUtils::ToJsonString(jsonObject);
    }

    std::string PutBucketEncryptionRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutBucketEncryptionRequest &r) {
        os << "PutBucketEncryptionRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
