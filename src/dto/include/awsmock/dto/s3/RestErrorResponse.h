//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_RESTERRORRESPONSE_H
#define AWSMOCK_DTO_S3_RESTERRORRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <iostream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

// AwsMok includes
#include "awsmock/core/ServiceException.h"

namespace AwsMock::Dto::S3 {

    struct RestErrorResponse {

      /**
       * Constructor.
       *
       * @param exc module exception
       */
      explicit RestErrorResponse(const Core::ServiceException &exc) {
          message = exc.message();
          code = exc.code();
          if(exc.requestId()) {
              requestId = std::string(exc.requestId());
          }
          if(exc.resource()) {
              requestId = std::string(exc.resource());
          }
      }

      /**
       * Error code
       */
     int code = 0;

      /**
       * Error message
       */
      std::string message;

      /**
       * Resource.
       *
       * <p>The bucket or object that is involved in the error.</p>
       */
      std::string resource;

      /**
       * Request ID
       */
      std::string requestId;

      /**
       * Converts the DTO to a XML string representation.
       *
       * @return DTO as XML string.
       */
      [[nodiscard]] std::string ToXml() const {
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

          // Root <Error>
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("Error");
          pDoc->appendChild(pRoot);

          // Code <Code>
          Poco::XML::AutoPtr<Poco::XML::Element> pCode = pDoc->createElement("Code");
          pRoot->appendChild(pCode);
          Poco::XML::AutoPtr<Poco::XML::Text> pCodeText = pDoc->createTextNode(std::to_string(code));
          pCode->appendChild(pCodeText);

          // Message <Message>
          Poco::XML::AutoPtr<Poco::XML::Element> pMessage = pDoc->createElement("Message");
          pRoot->appendChild(pMessage);
          Poco::XML::AutoPtr<Poco::XML::Text> pMessageText = pDoc->createTextNode(message);
          pMessage->appendChild(pMessageText);

          // Resource <Resource>
          if(!resource.empty()) {
              Poco::XML::AutoPtr<Poco::XML::Element> pResource = pDoc->createElement("Resource");
              pRoot->appendChild(pResource);
              Poco::XML::AutoPtr<Poco::XML::Text> pResourceText = pDoc->createTextNode(resource);
              pResource->appendChild(pResourceText);
          }

          // RequestId <RequestId>
          if(!requestId.empty()) {
              Poco::XML::AutoPtr<Poco::XML::Element> pRequestId = pDoc->createElement("RequestId");
              pRoot->appendChild(pRequestId);
              Poco::XML::AutoPtr<Poco::XML::Text> pRequestIdText = pDoc->createTextNode(requestId);
              pRequestId->appendChild(pRequestIdText);
          }

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
      friend std::ostream &operator<<(std::ostream &os, const RestErrorResponse &r) {
          os << "RestErrorResponse={code='" + std::to_string(r.code) + "' message='" + r.message + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_DTO_S3_RESTERRORRESPONSE_H