//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/s3/ListAllBucketResponse.h>

namespace AwsMock::Dto::S3 {

    std::string ListAllBucketResponse::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListAllMyBucketsResult");
        pDoc->appendChild(pRoot);

        Poco::XML::AutoPtr<Poco::XML::Element> pTotal = pDoc->createElement("Total");
        pRoot->appendChild(pTotal);
        Poco::XML::AutoPtr<Poco::XML::Text> pTotalText = pDoc->createTextNode(std::to_string(total));
        pTotal->appendChild(pTotalText);

        Poco::XML::AutoPtr<Poco::XML::Element> pBuckets;
        pBuckets = pDoc->createElement("Buckets");
        pRoot->appendChild(pBuckets);

        Poco::XML::AutoPtr<Poco::XML::Element> pBucket;
        Poco::XML::AutoPtr<Poco::XML::Element> pName;
        Poco::XML::AutoPtr<Poco::XML::Element> pCreated;
        Poco::XML::AutoPtr<Poco::XML::Text> pNameText;
        Poco::XML::AutoPtr<Poco::XML::Text> pCreatedText;
        for (auto &it: bucketList) {

            pBucket = pDoc->createElement("Bucket");
            pBuckets->appendChild(pBucket);

            pName = pDoc->createElement("Name");
            pBucket->appendChild(pName);
            pNameText = pDoc->createTextNode(it.name);
            pName->appendChild(pNameText);

            pCreated = pDoc->createElement("CreationDate");
            pBucket->appendChild(pCreated);
            pCreatedText = pDoc->createTextNode(Core::DateTimeUtils::ToISO8601(it.created));
            pCreated->appendChild(pCreatedText);
        }

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string ListAllBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListAllBucketResponse &r) {
        os << "ListAllBucketResponse={bucketList='";
        for (const auto &it: r.bucketList) {
            os << it.ToString() + ", ";
        }
        os << "'}";
        return os;
    }

}// namespace AwsMock::Dto::S3
