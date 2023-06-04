//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H
#define AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/NodeList.h"

namespace AwsMock::Dto::S3 {

    struct DeleteObjectsRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Bucket
       */
      std::string bucket;

      /**
       * Key
       */
      std::vector<std::string> keys;

      /**
       * Parse the delete objects request XML.
       *
       * @param xmlString notification XML string
       */
      void FromXml(const std::string &xmlString) {

          Poco::XML::DOMParser parser;
          Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

          Poco::XML::Node *deleteNode = pDoc->getNodeByPath("/Delete");
          if (deleteNode) {

              for (unsigned long i = 0; i < deleteNode->childNodes()->length(); i++) {
                  Poco::XML::Node *objectNode = deleteNode->childNodes()->item(i);
                  keys.push_back(objectNode->innerText());
              }
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
      friend std::ostream &operator<<(std::ostream &os, const DeleteObjectsRequest &r) {
          os << "DeleteObjectsRequest={region='" + r.region + "' bucket='" + r.bucket;
          for (auto &it : r.keys) {
              os << "' key='" + it;
          }
          os << "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_DELETEOBJECTSREQUEST_H
