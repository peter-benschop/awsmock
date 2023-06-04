//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/ListBucketResult.h>

namespace AwsMock::Dto::S3 {

    ListBucketResult::ListBucketResult(const std::string &bucket, Database::Entity::S3::ObjectList objectList) {

        _maxKeys = 1000;
        _name = bucket;

        if (objectList.empty()) {
            return;
        }

        for (auto &it : objectList) {
            Owner owner;
            owner.SetDisplayName(it.owner);
            owner.SetId(it.owner);

            Content content;
            content.SetKey(it.key);
            content.SetEtag(it.md5sum);
            content.SetSize(it.size);
            content.SetOwner(owner);
            content.SetStorageClass("STANDARD");
            content.SetLastModified(Poco::DateTimeFormatter::format(it.modified, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
            _contents.push_back(content);
        }
    }

    std::string ListBucketResult::ToXml() {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListBucketResult");
        pDoc->appendChild(pRoot);

        // IsTruncated
        Poco::XML::AutoPtr<Poco::XML::Element> pTruncated = pDoc->createElement("IsTruncated");
        pRoot->appendChild(pTruncated);
        Poco::XML::AutoPtr<Poco::XML::Text> pTruncatedText = pDoc->createTextNode(_isTruncated ? "true" : "false");
        pTruncated->appendChild(pTruncatedText);

        if (!_contents.empty()) {
            // Contents
            for (auto &it : _contents) {

                Poco::XML::AutoPtr<Poco::XML::Element> pContents = pDoc->createElement("Contents");
                pRoot->appendChild(pContents);

                // Check sum algorithms
                /*for(auto &cs : it.GetChecksumAlgorithms()) {
                    Poco::XML::AutoPtr<Poco::XML::Element> pCsAlgorithm = pDoc->createElement("ChecksumAlgorithm");
                    pContents->appendChild(pCsAlgorithm);
                    Poco::XML::AutoPtr<Poco::XML::Text> pCsAlgorithmText = pDoc->createTextNode(cs);
                    pCsAlgorithm->appendChild(pCsAlgorithmText);
                }*/

                // Key
                Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
                pContents->appendChild(pKey);
                Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(it.GetKey());
                pKey->appendChild(pKeyText);

                // LastModified
                Poco::XML::AutoPtr<Poco::XML::Element> pLastModified = pDoc->createElement("LastModified");
                pContents->appendChild(pLastModified);
                Poco::XML::AutoPtr<Poco::XML::Text> pLastModifiedText = pDoc->createTextNode(it.GetLastModified());
                pLastModified->appendChild(pLastModifiedText);

                // ETag
                Poco::XML::AutoPtr<Poco::XML::Element> pEtag = pDoc->createElement("ETag");
                pContents->appendChild(pEtag);
                Poco::XML::AutoPtr<Poco::XML::Text> pEtagText = pDoc->createTextNode(it.GetEtag());
                pEtag->appendChild(pEtagText);

                // Owner
                Poco::XML::AutoPtr<Poco::XML::Element> pOwner = pDoc->createElement("Owner");
                pContents->appendChild(pOwner);

                // DisplayName
                Poco::XML::AutoPtr<Poco::XML::Element> pDisplayName = pDoc->createElement("DisplayName");
                pOwner->appendChild(pDisplayName);
                Poco::XML::AutoPtr<Poco::XML::Text> pDisplayText = pDoc->createTextNode(it.GetOwner().GetDisplayName());
                pDisplayName->appendChild(pDisplayText);

                // ID
                Poco::XML::AutoPtr<Poco::XML::Element> pId = pDoc->createElement("ID");
                pOwner->appendChild(pId);
                Poco::XML::AutoPtr<Poco::XML::Text> pIdText = pDoc->createTextNode(it.GetOwner().GetId());
                pId->appendChild(pIdText);

                // Size
                Poco::XML::AutoPtr<Poco::XML::Element> pSize = pDoc->createElement("Size");
                pContents->appendChild(pSize);
                Poco::XML::AutoPtr<Poco::XML::Text> pSizeText = pDoc->createTextNode(std::to_string(it.GetSize()));
                pSize->appendChild(pSizeText);

                // StorageClass
                Poco::XML::AutoPtr<Poco::XML::Element> pStorageClass = pDoc->createElement("StorageClass");
                pContents->appendChild(pStorageClass);
                Poco::XML::AutoPtr<Poco::XML::Text> pStorageClassText = pDoc->createTextNode(it.GetStorageClass());
                pStorageClass->appendChild(pStorageClassText);
            }
        }
        // Name
        Poco::XML::AutoPtr<Poco::XML::Element> pName = pDoc->createElement("Name");
        pRoot->appendChild(pName);
        Poco::XML::AutoPtr<Poco::XML::Text> pNameText = pDoc->createTextNode(_name);
        pName->appendChild(pNameText);

        // Prefix
        Poco::XML::AutoPtr<Poco::XML::Element> pPrefix = pDoc->createElement("Prefix");
        pRoot->appendChild(pPrefix);
        Poco::XML::AutoPtr<Poco::XML::Text> pPrefixText = pDoc->createTextNode(_prefix);
        pPrefix->appendChild(pPrefixText);

        // Delimiter
        Poco::XML::AutoPtr<Poco::XML::Element> pDelimiter = pDoc->createElement("Delimiter");
        pRoot->appendChild(pPrefix);
        Poco::XML::AutoPtr<Poco::XML::Text> pDelimiterText = pDoc->createTextNode(_delimiter);
        pDelimiter->appendChild(pDelimiterText);

        // MaxKeys
        Poco::XML::AutoPtr<Poco::XML::Element> pMaxKeys = pDoc->createElement("MaxKeys");
        pRoot->appendChild(pMaxKeys);
        Poco::XML::AutoPtr<Poco::XML::Text> pMaxKeysText = pDoc->createTextNode(std::to_string(_maxKeys));
        pMaxKeys->appendChild(pMaxKeysText);

        // TODO: CommonPrefixes

        // EncodingType
        Poco::XML::AutoPtr<Poco::XML::Element> pEncodingType = pDoc->createElement("EncodingType");
        pRoot->appendChild(pEncodingType);
        Poco::XML::AutoPtr<Poco::XML::Text> pEncodingTypeText = pDoc->createTextNode(_encodingType);
        pEncodingType->appendChild(pEncodingTypeText);

        // KeyCount
        Poco::XML::AutoPtr<Poco::XML::Element> pKeyCount = pDoc->createElement("KeyCount");
        pRoot->appendChild(pKeyCount);
        Poco::XML::AutoPtr<Poco::XML::Text> pKeyCountText = pDoc->createTextNode(std::to_string(_keyCount));
        pKeyCount->appendChild(pKeyCountText);

        // ContinuationToken
        Poco::XML::AutoPtr<Poco::XML::Element> pContinuationToken = pDoc->createElement("ContinuationToken");
        pRoot->appendChild(pContinuationToken);
        Poco::XML::AutoPtr<Poco::XML::Text> pContinuationTokenText = pDoc->createTextNode(_continuationToken);
        pContinuationToken->appendChild(pContinuationTokenText);

        // NextContinuationToken
        Poco::XML::AutoPtr<Poco::XML::Element> pNextContinuationToken = pDoc->createElement("NextContinuationToken");
        pRoot->appendChild(pNextContinuationToken);
        Poco::XML::AutoPtr<Poco::XML::Text> pNextContinuationTokenText = pDoc->createTextNode(_nextContinuationToken);
        pNextContinuationToken->appendChild(pNextContinuationTokenText);

        // StartAfter
        Poco::XML::AutoPtr<Poco::XML::Element> pStartAfter = pDoc->createElement("StartAfter");
        pRoot->appendChild(pStartAfter);
        Poco::XML::AutoPtr<Poco::XML::Text> pStartAfterText = pDoc->createTextNode(_startAfter);
        pStartAfter->appendChild(pStartAfterText);

        std::stringstream output;
        Poco::XML::DOMWriter writer;
        writer.setNewLine("\n");
        writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
        writer.writeNode(output, pDoc);

        std::string outStr = output.str();
        return outStr;
    }

    /*std::string ListBucketResult::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListBucketResult &r) {
        os << "ListBucketResult={bucket='" + r._bucket + "', key='" + r._key + "', uploadId='" + r._uploadId + "'}";
        return os;
    }*/

}