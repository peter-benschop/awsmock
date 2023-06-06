//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LISTBUCKETRESULT_H
#define AWSMOCK_DTO_S3_LISTBUCKETRESULT_H

// C++ Standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

// AwsMock includes
#include <awsmock/entity/s3/Object.h>

namespace AwsMock::Dto::S3 {

    struct Owner {

      /**
       * ID
       */
      std::string id;

      /**
       * Display name
       */
      std::string displayName;

    };

    struct Content {

      /**
       * Checksum algorithms
       */
      std::vector<std::string> checksumAlgorithms;

      /**
       * ETag
       */
      std::string etag;

      /**
       * Key
       */
      std::string key;

      /**
       * Last modified
       */
      std::string lastModified;

      /**
       * Owner
       */
      Owner owner;

      /**
       * Size
       */
      long size = 0;

      /**
       * Storage class
       */
      std::string storageClass;
    };

    struct CommonPrefix {

      /**
       * Prefix
       */
      std::string _prefix;
    };

    struct ListBucketResult {

      /**
       * Truncation flag
       */
      bool isTruncated = false;

      /**
       * Contents
       */
      std::vector<Content> contents;

      /**
       * Name
       */
      std::string name;

      /**
       * Prefix
       */
      std::string prefix;

      /**
       * Delimiter
       */
      std::string delimiter;

      /**
       * Maximal keys
       */
      int maxKeys = 1000;

      /**
       * Encoding type
       */
      std::string encodingType;

      /**
       * Key count
       */
      int keyCount = 0;

      /**
       * Continuation token
       */
      std::string continuationToken;

      /**
       * Next continuation token
       */
      std::string nextContinuationToken;

      /**
       * Start after
       */
      std::string startAfter;

      /**
       * Constructor
       *
       * @param bucket bucket
       * @param objectList object list
       */
      ListBucketResult(const std::string &bucket, Database::Entity::S3::ObjectList objectList) {

          maxKeys = 1000;
          name = bucket;

          if (objectList.empty()) {
              return;
          }

          for (auto &it : objectList) {
              Owner owner;
              owner.displayName = it.owner;
              owner.id = it.owner;

              Content content;
              content.key = it.key;
              content.etag = it.md5sum;
              content.size = it.size;
              content.owner = owner;
              content.storageClass="STANDARD";
              content.lastModified = Poco::DateTimeFormatter::format(it.modified, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT);
              contents.push_back(content);
          }
      }
      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml() {

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
              for (auto &it : contents) {

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

          std::stringstream output;
          Poco::XML::DOMWriter writer;
          writer.setNewLine("\n");
          writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
          writer.writeNode(output, pDoc);

          std::string outStr = output.str();
          return outStr;
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const ListBucketResult &r) {
          os << "ListBucketResult={name='" + r.name + "' prefix='" + r.prefix + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_LISTBUCKETRESULT_H
