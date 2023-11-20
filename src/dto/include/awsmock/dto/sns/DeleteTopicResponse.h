//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETETOPICSRESPONSE_H
#define AWSMOCK_DTO_SQS_DELETETOPICSRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <iostream>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"

// AwsMock includes
#include "awsmock/core/ServiceException.h"
#include "awsmock/entity/sns/Topic.h"

namespace AwsMock::Dto::SNS {

  struct DeleteTopicResponse {

    /**
     * Convert to XML representation
     *
     * @return XML string
     */
    [[nodiscard]] std::string ToXml() const {

      // XML Document
      Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

      // Root element
      Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("DeleteTopicResponse");
      pDoc->appendChild(pRoot);

      // Metadata
      Poco::XML::AutoPtr<Poco::XML::Element> pMetaData = pDoc->createElement("ResponseMetadata");
      pRoot->appendChild(pMetaData);

      Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
      pMetaData->appendChild(pRequestId);
      Poco::XML::AutoPtr<Poco::XML::Text> pRequestText = pDoc->createTextNode(Poco::UUIDGenerator().createRandom().toString());
      pRequestId->appendChild(pRequestText);

      std::stringstream output;
      Poco::XML::DOMWriter writer;
      writer.setNewLine("\n");
      writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION | Poco::XML::XMLWriter::PRETTY_PRINT);
      writer.writeNode(output, pDoc);

      return output.str();
    }
  };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SQS_DELETETOPICSRESPONSE_H
