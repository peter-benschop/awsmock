//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/CompleteMultipartUploadResult.h"

namespace AwsMock::Dto::S3 {

    CompleteMultipartUploadResult::CompleteMultipartUploadResult(const std::string &location, const std::string &bucket, const std::string &key, const std::string &etag)
        : _location(location), _bucket(bucket), _key(key), _etag(etag) {
    }

    std::string CompleteMultipartUploadResult::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CompleteMultipartUploadResult");
        pDoc->appendChild(pRoot);

        Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("Location");
        pRoot->appendChild(pLocation);
        Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(_location);
        pLocation->appendChild(pLocationText);

        Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
        pRoot->appendChild(pBucket);
        Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(_bucket);
        pBucket->appendChild(pBucketText);

        Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
        pRoot->appendChild(pKey);
        Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(_key);
        pKey->appendChild(pKeyText);

        Poco::XML::AutoPtr<Poco::XML::Element> pEtag = pDoc->createElement("ETag");
        pRoot->appendChild(pEtag);
        Poco::XML::AutoPtr<Poco::XML::Text> pEtagText = pDoc->createTextNode(_etag);
        pEtag->appendChild(pEtagText);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::string outStr = output.str();
        return outStr;
    }

    std::string CompleteMultipartUploadResult::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadResult &r) {
        os << "InitiateMultipartUploadResult={location='" + r._location + ", bucket='" + r._bucket + "', key='" + r._key + "', etag='" + r._etag + "'}";
        return os;
    }

}