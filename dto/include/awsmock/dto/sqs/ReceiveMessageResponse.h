//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H
#define AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

// AwsMock includes
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Dto::SQS {

    struct ReceiveMessageResponse {

      Database::Entity::SQS::MessageList messageList;

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
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("ReceiveMessageResponse");
          pDoc->appendChild(pRoot);

          // ReceiveMessageResult
          Poco::XML::AutoPtr<Poco::XML::Element> pResult = pDoc->createElement("ReceiveMessageResult");
          pRoot->appendChild(pResult);

          for(auto &it : messageList) {

              // Message
              Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
              pResult->appendChild(pMessage);

              // MessageId
              Poco::XML::AutoPtr<Poco::XML::Element> pMessageId = pDoc->createElement("MessageId");
              pMessage->appendChild(pMessageId);
              Poco::XML::AutoPtr<Poco::XML::Text> pMessageIdText = pDoc->createTextNode(it.messageId);
              pMessage->appendChild(pMessageIdText);

              // ReceiptHandle
              Poco::XML::AutoPtr<Poco::XML::Element> pReceiptHandle = pDoc->createElement("ReceiptHandle");
              pMessage->appendChild(pReceiptHandle);
              Poco::XML::AutoPtr<Poco::XML::Text> pReceiptHandleText = pDoc->createTextNode(it.receiptHandle);
              pReceiptHandle->appendChild(pReceiptHandleText);

              // MD5OfBody
              Poco::XML::AutoPtr<Poco::XML::Element> pMd5Body = pDoc->createElement("MD5OfBody");
              pMessage->appendChild(pMd5Body);
              Poco::XML::AutoPtr<Poco::XML::Text> pMd5BodyText = pDoc->createTextNode(it.md5Body);
              pMd5Body->appendChild(pReceiptHandleText);

              // Body
              Poco::XML::AutoPtr<Poco::XML::Element> pBody = pDoc->createElement("Body");
              pMessage->appendChild(pBody);
              Poco::XML::AutoPtr<Poco::XML::Text> pBodyText = pDoc->createTextNode(it.body);
              pBody->appendChild(pBodyText);

                for(auto &at : it.attributeList) {

                    // Attribute
                    Poco::XML::AutoPtr<Poco::XML::Element> pAttribute = pDoc->createElement("Attribute");
                    pMessage->appendChild(pAttribute);

                    // Name
                    Poco::XML::AutoPtr<Poco::XML::Element> pAttrName = pDoc->createElement("Name");
                    pAttribute->appendChild(pAttrName);
                    Poco::XML::AutoPtr<Poco::XML::Text> pAttrNameText = pDoc->createTextNode(at.name);
                    pAttrName->appendChild(pDoc->createTextNode(at.name));

                    // Value
                    Poco::XML::AutoPtr<Poco::XML::Element> pAttrValue = pDoc->createElement("Value");
                    pAttribute->appendChild(pAttrValue);
                    Poco::XML::AutoPtr<Poco::XML::Text> pAttrValueText = pDoc->createTextNode(at.value);
                    pAttrValue->appendChild(pAttrValueText);
                }
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
      friend std::ostream &operator<<(std::ostream &os, const ReceiveMessageResponse &r) {
          os << "ReceiveMessageResponse={resource='" + r.resource + "' requestId: '" + r.requestId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H
