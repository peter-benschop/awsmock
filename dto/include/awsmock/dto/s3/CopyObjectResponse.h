//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_COPYOBJECTSRESPONSE_H
#define AWSMOCK_DTO_S3_COPYOBJECTSRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    struct CopyObjectResponse {

      /**
       * Etag
       */
      std::string eTag;

      /**
       * Last modified
       */
      std::string lastModified;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CopyObjectResult");
          pDoc->appendChild(pRoot);

          // ETag
          Poco::XML::AutoPtr<Poco::XML::Element> pETag = pDoc->createElement("ETag");
          pRoot->appendChild(pETag);
          Poco::XML::AutoPtr<Poco::XML::Text> pETagText = pDoc->createTextNode(eTag);
          pETag->appendChild(pETagText);

          // LastModified
          Poco::XML::AutoPtr<Poco::XML::Element> pLastModified = pDoc->createElement("LastModified");
          pRoot->appendChild(pLastModified);
          Poco::XML::AutoPtr<Poco::XML::Text> pLastModifiedTest = pDoc->createTextNode(lastModified);
          pLastModified->appendChild(pLastModifiedTest);

          std::stringstream output;
          Poco::XML::DOMWriter writer;
          writer.setNewLine("\n");
          writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
          writer.writeNode(output, pDoc);

          return output.str();
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
      friend std::ostream &operator<<(std::ostream &os, const CopyObjectResponse &r) {
          os << "CopyObjectResponse={eTag:'" + r.eTag + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H
