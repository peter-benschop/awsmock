//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H
#define AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    struct CompleteMultipartUploadResult {

      /**
       * AWS location
       */
      std::string location;

      /**
       * Bucket name
       */
      std::string bucket;

      /**
       * Key name
       */
      std::string key;

      /**
       * ETag
       */
      std::string etag;

      /**
       * Checksum CRC32
       */
      std::string checksumCrc32;

      /**
       * Checksum CRC32C
       */
      std::string checksumCrc32c;

      /**
       * Checksum SHA1
       */
      std::string checksumSha1;

      /**
       * Checksum SHA256
       */
      std::string checksumSha256;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml() const {
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CompleteMultipartUploadResult");
          pDoc->appendChild(pRoot);

          Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("Location");
          pRoot->appendChild(pLocation);
          Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(location);
          pLocation->appendChild(pLocationText);

          Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
          pRoot->appendChild(pBucket);
          Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(bucket);
          pBucket->appendChild(pBucketText);

          Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
          pRoot->appendChild(pKey);
          Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(key);
          pKey->appendChild(pKeyText);

          Poco::XML::AutoPtr<Poco::XML::Element> pEtag = pDoc->createElement("ETag");
          pRoot->appendChild(pEtag);
          Poco::XML::AutoPtr<Poco::XML::Text> pEtagText = pDoc->createTextNode(etag);
          pEtag->appendChild(pEtagText);

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
      friend std::ostream &operator<<(std::ostream &os, const CompleteMultipartUploadResult &r) {
          os << "CompleteMultipartUploadResult={location='" + r.location + ", bucket='" + r.bucket + "', key='" + r.key + "', etag='" + r.etag +
          "' checksumCrc32='" +r.checksumCrc32 + "' checksumCrc32c='" + r.checksumCrc32c + " checksumSha1='" + r.checksumSha1 +
          "' checksumSha256='" + r.checksumSha256 + "'}";
          return os;
      }
    };

 } // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H
