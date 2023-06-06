//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H
#define AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H

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

namespace AwsMock::Dto::SQS {

    struct CreateMessageResponse {

      /**
       * ID
       */
      long id;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Message ID
       */
      std::string messageId;

      /**
       * Receipt handle
       */
      std::string receiptHandle;

      /**
       * MD5 sum of body
       */
      std::string md5Body;

      /**
       * MD5 sum of sqs
       */
      std::string md5Attr;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      [[nodiscard]] std::string ToXml() const {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("SendMessageResponse");
          pDoc->appendChild(pRoot);

          // SendMessageResult
          Poco::XML::AutoPtr<Poco::XML::Element> pSendMessageResult = pDoc->createElement("SendMessageResult");
          pRoot->appendChild(pSendMessageResult);

          // MessageID
          Poco::XML::AutoPtr<Poco::XML::Element> pMessageId = pDoc->createElement("MessageId");
          pSendMessageResult->appendChild(pMessageId);
          Poco::XML::AutoPtr<Poco::XML::Text> pMessageIdText = pDoc->createTextNode(messageId);
          pMessageId->appendChild(pMessageIdText);

          // MD5 body
          Poco::XML::AutoPtr<Poco::XML::Element> pMd5Body = pDoc->createElement("MD5OfMessageBody");
          pSendMessageResult->appendChild(pMd5Body);
          Poco::XML::AutoPtr<Poco::XML::Text> pMd5BodyText = pDoc->createTextNode(md5Body);
          pMd5Body->appendChild(pMd5BodyText);

          // MD5 sqs
          Poco::XML::AutoPtr<Poco::XML::Element> pMd5Attr = pDoc->createElement("MD5OfMessageAttributes");
          pSendMessageResult->appendChild(pMd5Attr);
          Poco::XML::AutoPtr<Poco::XML::Text> pMd5AttrText = pDoc->createTextNode(md5Attr);
          pMd5Attr->appendChild(pMd5AttrText);

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
      friend std::ostream &operator<<(std::ostream &os, const CreateMessageResponse &r) {
          os << "CreateMessageResponse={id='" + std::to_string(r.id) + "' url='" + r.queueUrl + "' messageId='" + r.messageId + "' receiptHandle='" + r.receiptHandle +
              "' md5body='" + r.md5Body + "' md5attr='" + r.md5Attr + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H
