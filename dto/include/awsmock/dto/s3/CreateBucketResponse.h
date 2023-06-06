//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H
#define AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H

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

    struct CreateBucketResponse {

      /**
       * Bucket location
       */
      std::string location;

      /**
       * Bucket ARN
       */
      std::string arn;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketResult");
          pDoc->appendChild(pRoot);
          Poco::XML::AutoPtr<Poco::XML::Element> pChild1 = pDoc->createElement("BuckerArn");
          pRoot->appendChild(pChild1);
          Poco::XML::AutoPtr<Poco::XML::Text> pText1 = pDoc->createTextNode(arn);
          pChild1->appendChild(pText1);

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
      friend std::ostream &operator<<(std::ostream &os, const CreateBucketResponse &r) {
          os << "CreateBucketResponse={bucket='" + r.location + "', arn='" + r.arn + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_CREATEBUCKETRESPONSE_H
