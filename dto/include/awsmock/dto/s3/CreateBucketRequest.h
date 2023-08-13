//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_S3CREATEBUCKETREQUEST_H
#define AWSMOCK_CORE_DTO_S3CREATEBUCKETREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    struct CreateBucketRequest {

      /**
       * Bucket location
       */
      std::string _locationConstraint;

      /**
       * Constructor
       *
       * @param xmlString XML string
       */
      explicit CreateBucketRequest(const std::string &xmlString) {
          FromXml(xmlString);
      }

      /**
       * Convert from XML representation
       *
       * @param xmlString XML string
       */
      void FromXml(const std::string &xmlString) {

          Poco::XML::DOMParser parser;
          Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

          Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
          _locationConstraint = node->innerText();
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
      friend std::ostream &operator<<(std::ostream &os, const CreateBucketRequest &r) {
          os << "CreateBucketRequest={locationConstraint='" + r._locationConstraint + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::s3

#endif //AWSMOCK_CORE_DTO_S3CREATEBUCKETREQUEST_H
