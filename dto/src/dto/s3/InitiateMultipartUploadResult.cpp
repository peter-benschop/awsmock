//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/InitiateMultipartUploadResult.h"

namespace AwsMock::Dto::S3 {

    InitiateMultipartUploadResult::InitiateMultipartUploadResult(const std::string &bucket, const std::string &key, const std::string &uploadId)
        : _bucket(bucket), _key(key), _uploadId(uploadId) {
    }

    std::string InitiateMultipartUploadResult::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("InitiateMultipartUploadResult");
        pDoc->appendChild(pRoot);

        Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
        pRoot->appendChild(pBucket);
        Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(_bucket);
        pBucket->appendChild(pBucketText);

        Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
        pRoot->appendChild(pKey);
        Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(_key);
        pKey->appendChild(pKeyText);

        Poco::XML::AutoPtr<Poco::XML::Element> pUploadId = pDoc->createElement("UploadId");
        pRoot->appendChild(pUploadId);
        Poco::XML::AutoPtr<Poco::XML::Text> pUploadIdText = pDoc->createTextNode(_uploadId);
        pUploadId->appendChild(pUploadIdText);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::string outStr = output.str();
        return outStr;
    }

    std::string InitiateMultipartUploadResult::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const InitiateMultipartUploadResult &r) {
        os << "InitiateMultipartUploadResult={bucket='" + r._bucket + "', key='" + r._key + "', uploadId='" + r._uploadId + "'}";
        return os;
    }

}