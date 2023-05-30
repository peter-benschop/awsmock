//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/s3/ListAllBucketResponse.h"

namespace AwsMock::Dto::S3 {

    ListAllBucketResponse::ListAllBucketResponse(BucketList bucketList) : _bucketList(bucketList) {
    }

    std::string ListAllBucketResponse::ToXml() {
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListAllMyBucketsResult");
        pDoc->appendChild(pRoot);

        Poco::XML::AutoPtr<Poco::XML::Element> pBucket;
        Poco::XML::AutoPtr<Poco::XML::Element> pName;
        Poco::XML::AutoPtr<Poco::XML::Element> pCreated;
        Poco::XML::AutoPtr<Poco::XML::Text> pNameText;
        Poco::XML::AutoPtr<Poco::XML::Text> pCreatedText;
        for (auto &it : _bucketList) {
            pBucket = pDoc->createElement("Bucket");
            pRoot->appendChild(pBucket);

            pName = pDoc->createElement("String");
            pBucket->appendChild(pName);

            pCreated = pDoc->createElement("CreationDate");
            pBucket->appendChild(pCreated);

            pNameText = pDoc->createTextNode(it.name);
            pName->appendChild(pNameText);

            pCreatedText = pDoc->createTextNode(Poco::DateTimeFormatter::format(it.creationDatetime, Poco::DateTimeFormat::HTTP_FORMAT));
            pCreated->appendChild(pCreatedText);
        }

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::string outStr = output.str();
        return outStr;
    }

    std::string ListAllBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListAllBucketResponse &r) {
        //os << "CreateBucketRequest={locationConstraint='" + r._location + "', arn='" + r._arn + "'}";
        return os;
    }

}