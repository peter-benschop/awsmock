//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_DELETEOBJECTSRESPONSE_H
#define AWSMOCK_DTO_S3_DELETEOBJECTSRESPONSE_H

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

    struct DeleteObjectsResponse {

      /**
       * Keys
       */
      std::vector<std::string> keys;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml() const {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("DeleteResult");
          pDoc->appendChild(pRoot);

          for(auto it:keys) {

              // Deleted
              Poco::XML::AutoPtr<Poco::XML::Element> pDeleted = pDoc->createElement("Deleted");
              pRoot->appendChild(pDeleted);

              // Key
              Poco::XML::AutoPtr<Poco::XML::Element> pKey = pDoc->createElement("Key");
              pDeleted->appendChild(pKey);
              Poco::XML::AutoPtr<Poco::XML::Text> pKeyText = pDoc->createTextNode(it);
              pKey->appendChild(pKeyText);
          }
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
      friend std::ostream &operator<<(std::ostream &os, const DeleteObjectsResponse &r) {
          os << "DeleteObjectsResponse={";
          for (auto &it : r.keys) {
              os << "' key='" + it;
          }
          os << "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H
