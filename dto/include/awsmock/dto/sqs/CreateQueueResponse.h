//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEQUEUERESPONSE_H
#define AWSMOCK_DTO_SQS_CREATEQUEUERESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

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

namespace AwsMock::Dto::SQS {

    struct CreateQueueResponse {

      /**
       * Region
       */
      std::string region;

      /**
       * Name
       */
      std::string name;

      /**
       * Owner
       */
      std::string owner;

      /**
       * URL
       */
      std::string url;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("CreateQueueResponse");
          pDoc->appendChild(pRoot);

          // CreateQueueResult
          Poco::XML::AutoPtr<Poco::XML::Element> pListQueueResult = pDoc->createElement("CreateQueueResult");
          pRoot->appendChild(pListQueueResult);

          Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrl = pDoc->createElement("QueueUrl");
          pListQueueResult->appendChild(pQueueUrl);
          Poco::XML::AutoPtr<Poco::XML::Text> pQueueUrlText = pDoc->createTextNode(url);
          pQueueUrl->appendChild(pQueueUrlText);

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
      friend std::ostream &operator<<(std::ostream &os, const CreateQueueResponse &r) {
          os << "CreateQueueResponse={region='" + r.region + "' name='" + r.name + "' owner='" + r.owner + "' url='" + r.url + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEQUEUERESPONSE_H
