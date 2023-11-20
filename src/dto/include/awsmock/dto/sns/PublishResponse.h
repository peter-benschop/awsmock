//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_PUBLISRESPONSE_H
#define AWSMOCK_DTO_SNS_PUBLISRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <utility>

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

namespace AwsMock::Dto::SNS {

  struct PublishResponse {

    /**
     * Message ID
     */
    std::string messageId;

    /**
     * Convert to XML representation
     *
     * @return XML string
     */
    [[nodiscard]] std::string ToXml() const {

      // Root
      Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
      Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("PublishResponse");
      pDoc->appendChild(pRoot);

      // SendMessageResult
      Poco::XML::AutoPtr<Poco::XML::Element> pSendMessageResult = pDoc->createElement("PublishResult");
      pRoot->appendChild(pSendMessageResult);

      // MessageID
      Poco::XML::AutoPtr<Poco::XML::Element> pMessageId = pDoc->createElement("MessageId");
      pSendMessageResult->appendChild(pMessageId);
      Poco::XML::AutoPtr<Poco::XML::Text> pMessageIdText = pDoc->createTextNode(messageId);
      pMessageId->appendChild(pMessageIdText);

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
    friend std::ostream &operator<<(std::ostream &os, const PublishResponse &r) {
      os << "PublishResponse={messageId='" + r.messageId + "'}";
      return os;
    }

  };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SNS_PUBLISRESPONSE_H
