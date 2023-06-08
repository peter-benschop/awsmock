//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_INITIATEMULTIPARTUPLOADRESULT_H
#define AWSMOCK_DTO_S3_INITIATEMULTIPARTUPLOADRESULT_H

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

    struct InitiateMultipartUploadResult {

      /**
       * Bucket name
       */
      std::string bucket;

      /**
       * Key name
       */
      std::string key;

      /**
       * Upload ID
       */
      std::string uploadId;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("InitiateMultipartUploadResult");
          pDoc->appendChild(pRoot);

          Poco::XML::AutoPtr<Poco::XML::Element> pBucket = pDoc->createElement("Bucket");
          pRoot->appendChild(pBucket);
          Poco::XML::AutoPtr<Poco::XML::Text> pBucketText = pDoc->createTextNode(bucket);
          pBucket->appendChild(pBucketText);

          Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
          pRoot->appendChild(pKey);
          Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(key);
          pKey->appendChild(pKeyText);

          Poco::XML::AutoPtr<Poco::XML::Element> pUploadId = pDoc->createElement("UploadId");
          pRoot->appendChild(pUploadId);
          Poco::XML::AutoPtr<Poco::XML::Text> pUploadIdText = pDoc->createTextNode(uploadId);
          pUploadId->appendChild(pUploadIdText);

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
      friend std::ostream &operator<<(std::ostream &os, const InitiateMultipartUploadResult &r) {
          os << "InitiateMultipartUploadResult={bucket='" + r.bucket + "', key='" + r.key + "', uploadId='" + r.uploadId + "'}";
          return os;
      }
    };

 } // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_INITIATEMULTIPARTUPLOADRESULT_H
