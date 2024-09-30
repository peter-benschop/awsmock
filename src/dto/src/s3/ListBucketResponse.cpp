
#include <awsmock/dto/s3/ListBucketResponse.h>

namespace AwsMock::Dto::S3 {

    ListBucketResponse::ListBucketResponse(const std::string &bucket, const Database::Entity::S3::ObjectList &objectList) {

        maxKeys = 1000;
        name = bucket;

        if (objectList.empty()) {
            return;
        }

        for (auto &it: objectList) {
            Owner owner;
            owner.displayName = it.owner;
            owner.id = it.owner;

            Content content;
            content.key = it.key;
            content.etag = it.md5sum;
            content.size = it.size;
            content.owner = owner;
            content.storageClass = "STANDARD";
            content.lastModified = Core::DateTimeUtils::ISO8601(it.modified);
            contents.push_back(content);
        }
    }

    std::string ListBucketResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("isTruncated", isTruncated);
            rootJson.set("name", name);
            rootJson.set("prefix", prefix);
            rootJson.set("delimiter", delimiter);
            rootJson.set("maxKeys", maxKeys);
            rootJson.set("encodingType", encodingType);
            rootJson.set("keyCount", keyCount);
            rootJson.set("continuationToken", continuationToken);
            rootJson.set("nextContinuationToken", nextContinuationToken);
            rootJson.set("startAfter", startAfter);
            rootJson.set("total", total);

            // Contents
            if (!contents.empty()) {

                Poco::JSON::Array jsonContentArray;
                for (auto &it: contents) {
                    Poco::JSON::Object jsonObject;
                    jsonObject.set("key", it.key);
                    jsonObject.set("modified", it.lastModified);
                    jsonObject.set("etag", it.etag);
                    jsonObject.set("owner", it.owner);
                    jsonObject.set("displayName", it.owner.displayName);
                    jsonObject.set("id", it.owner.id);
                    jsonObject.set("size", it.size);
                    jsonObject.set("storageClass", it.storageClass);
                    jsonContentArray.add(jsonObject);
                }

                rootJson.set("content", jsonContentArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListBucketResponse::ToXml() {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ListBucketResult");
        pDoc->appendChild(pRoot);

        // IsTruncated
        Poco::XML::AutoPtr<Poco::XML::Element> pTruncated = pDoc->createElement("IsTruncated");
        pRoot->appendChild(pTruncated);
        Poco::XML::AutoPtr<Poco::XML::Text> pTruncatedText = pDoc->createTextNode(isTruncated ? "true" : "false");
        pTruncated->appendChild(pTruncatedText);

        if (!contents.empty()) {
            // Contents
            for (auto &it: contents) {

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
                Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(it.key);
                pKey->appendChild(pKeyText);

                // LastModified
                Poco::XML::AutoPtr<Poco::XML::Element> pLastModified = pDoc->createElement("LastModified");
                pContents->appendChild(pLastModified);
                Poco::XML::AutoPtr<Poco::XML::Text> pLastModifiedText = pDoc->createTextNode(it.lastModified);
                pLastModified->appendChild(pLastModifiedText);

                // ETag
                Poco::XML::AutoPtr<Poco::XML::Element> pEtag = pDoc->createElement("ETag");
                pContents->appendChild(pEtag);
                Poco::XML::AutoPtr<Poco::XML::Text> pEtagText = pDoc->createTextNode(it.etag);
                pEtag->appendChild(pEtagText);

                // Owner
                Poco::XML::AutoPtr<Poco::XML::Element> pOwner = pDoc->createElement("Owner");
                pContents->appendChild(pOwner);

                // DisplayName
                Poco::XML::AutoPtr<Poco::XML::Element> pDisplayName = pDoc->createElement("DisplayName");
                pOwner->appendChild(pDisplayName);
                Poco::XML::AutoPtr<Poco::XML::Text> pDisplayText = pDoc->createTextNode(it.owner.displayName);
                pDisplayName->appendChild(pDisplayText);

                // ID
                Poco::XML::AutoPtr<Poco::XML::Element> pId = pDoc->createElement("ID");
                pOwner->appendChild(pId);
                Poco::XML::AutoPtr<Poco::XML::Text> pIdText = pDoc->createTextNode(it.owner.id);
                pId->appendChild(pIdText);

                // Size
                Poco::XML::AutoPtr<Poco::XML::Element> pSize = pDoc->createElement("Size");
                pContents->appendChild(pSize);
                Poco::XML::AutoPtr<Poco::XML::Text> pSizeText = pDoc->createTextNode(std::to_string(it.size));
                pSize->appendChild(pSizeText);

                // StorageClass
                Poco::XML::AutoPtr<Poco::XML::Element> pStorageClass = pDoc->createElement("StorageClass");
                pContents->appendChild(pStorageClass);
                Poco::XML::AutoPtr<Poco::XML::Text> pStorageClassText = pDoc->createTextNode(it.storageClass);
                pStorageClass->appendChild(pStorageClassText);
            }
        }
        // Name
        Poco::XML::AutoPtr<Poco::XML::Element> pName = pDoc->createElement("Name");
        pRoot->appendChild(pName);
        Poco::XML::AutoPtr<Poco::XML::Text> pNameText = pDoc->createTextNode(name);
        pName->appendChild(pNameText);

        // Prefix
        Poco::XML::AutoPtr<Poco::XML::Element> pPrefix = pDoc->createElement("Prefix");
        pRoot->appendChild(pPrefix);
        Poco::XML::AutoPtr<Poco::XML::Text> pPrefixText = pDoc->createTextNode(prefix);
        pPrefix->appendChild(pPrefixText);

        // Delimiter
        Poco::XML::AutoPtr<Poco::XML::Element> pDelimiter = pDoc->createElement("Delimiter");
        pRoot->appendChild(pPrefix);
        Poco::XML::AutoPtr<Poco::XML::Text> pDelimiterText = pDoc->createTextNode(delimiter);
        pDelimiter->appendChild(pDelimiterText);

        // MaxKeys
        Poco::XML::AutoPtr<Poco::XML::Element> pMaxKeys = pDoc->createElement("MaxKeys");
        pRoot->appendChild(pMaxKeys);
        Poco::XML::AutoPtr<Poco::XML::Text> pMaxKeysText = pDoc->createTextNode(std::to_string(maxKeys));
        pMaxKeys->appendChild(pMaxKeysText);

        // TODO: CommonPrefixes

        // EncodingType
        Poco::XML::AutoPtr<Poco::XML::Element> pEncodingType = pDoc->createElement("EncodingType");
        pRoot->appendChild(pEncodingType);
        Poco::XML::AutoPtr<Poco::XML::Text> pEncodingTypeText = pDoc->createTextNode(encodingType);
        pEncodingType->appendChild(pEncodingTypeText);

        // KeyCount
        Poco::XML::AutoPtr<Poco::XML::Element> pKeyCount = pDoc->createElement("KeyCount");
        pRoot->appendChild(pKeyCount);
        Poco::XML::AutoPtr<Poco::XML::Text> pKeyCountText = pDoc->createTextNode(std::to_string(keyCount));
        pKeyCount->appendChild(pKeyCountText);

        // ContinuationToken
        Poco::XML::AutoPtr<Poco::XML::Element> pContinuationToken = pDoc->createElement("ContinuationToken");
        pRoot->appendChild(pContinuationToken);
        Poco::XML::AutoPtr<Poco::XML::Text> pContinuationTokenText = pDoc->createTextNode(continuationToken);
        pContinuationToken->appendChild(pContinuationTokenText);

        // NextContinuationToken
        Poco::XML::AutoPtr<Poco::XML::Element> pNextContinuationToken = pDoc->createElement("NextContinuationToken");
        pRoot->appendChild(pNextContinuationToken);
        Poco::XML::AutoPtr<Poco::XML::Text> pNextContinuationTokenText = pDoc->createTextNode(nextContinuationToken);
        pNextContinuationToken->appendChild(pNextContinuationTokenText);

        // StartAfter
        Poco::XML::AutoPtr<Poco::XML::Element> pStartAfter = pDoc->createElement("StartAfter");
        pRoot->appendChild(pStartAfter);
        Poco::XML::AutoPtr<Poco::XML::Text> pStartAfterText = pDoc->createTextNode(startAfter);
        pStartAfter->appendChild(pStartAfterText);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    [[nodiscard]] std::string ListBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListBucketResponse &r) {
        os << "ListBucketResult=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3