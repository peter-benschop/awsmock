//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H
#define AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::SQS {

    struct GetQueueAttributesResponse {

      /**
       * Attributes
       */
      std::vector<std::pair<std::string, std::string>> attributes;

      /**
       * Resource
       */
      std::string resource = "SQS";

      /**
       * Resource
       */
      std::string requestId = Poco::UUIDGenerator().createRandom().toString();

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetQueueAttributesResponse");
          pDoc->appendChild(pRoot);

          // Metadata
          Poco::XML::AutoPtr<Poco::XML::Element> pAttributeResult = pDoc->createElement("GetQueueAttributesResult");
          pRoot->appendChild(pAttributeResult);

          for (const auto &attribute : attributes) {

              // Attribute
              Poco::XML::AutoPtr<Poco::XML::Element> pAttribute = pDoc->createElement("Attribute");
              pAttributeResult->appendChild(pAttribute);

              // Name
              Poco::XML::AutoPtr<Poco::XML::Element> pName = pDoc->createElement("Name");
              pAttribute->appendChild(pName);
              Poco::XML::AutoPtr<Poco::XML::Text> pNameText = pDoc->createTextNode(attribute.first);
              pName->appendChild(pNameText);

              // Value
              Poco::XML::AutoPtr<Poco::XML::Element> pValue = pDoc->createElement("Value");
              pAttribute->appendChild(pValue);
              Poco::XML::AutoPtr<Poco::XML::Text> pValueText = pDoc->createTextNode(attribute.second);
              pValue->appendChild(pValueText);
          }

          // Metadata
          Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
          pRoot->appendChild(pMetaData);

          Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
          pMetaData->appendChild(pRequestId);
          Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(requestId);
          pRequestId->appendChild(pRequestText);

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
      friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesResponse &r) {
          os << "GetQueueAttributesResponse={resource='" + r.resource + "' requestId: '" + r.requestId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H
