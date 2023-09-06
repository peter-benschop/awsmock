//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H
#define AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H

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

    struct CreateBucketConstraint {

      /**
       * Bucket location
       */
      std::string location;

      /**
       * Convert to XML representation
       *
       * <CreateBucketConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
       *     <LocationConstraint>eu-central-1</LocationConstraint>
       * </CreateBucketConfiguration>
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateBucketConfiguration");
          pDoc->appendChild(pRoot);

          Poco::XML::AutoPtr<Poco::XML::Element> pLocation = pDoc->createElement("LocationConstraint");
          pRoot->appendChild(pLocation);
          Poco::XML::AutoPtr<Poco::XML::Text> pLocationText = pDoc->createTextNode(location);
          pLocation->appendChild(pLocationText);

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
      friend std::ostream &operator<<(std::ostream &os, const CreateBucketConstraint &r) {
          os << "CreateBucketConstraint={location='" + r.location + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_S3_CREATEBUCKETCONSTRAINT_H
