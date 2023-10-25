//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEURLRESPONSE_H
#define AWSMOCK_DTO_SQS_GETQUEUEURLRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/XML/XMLWriter.h"

// AwsMock includes
#include <awsmock/core/ServiceException.h>

/**
 * <?xml version="1.0"?>
 * <GetQueueUrlResponse xmlns="http://queue.amazonaws.com/doc/2012-11-05/">
 *     <GetQueueUrlResult>
 *         <QueueUrl>https://sqs.us-east-1.amazonaws.com/177715257436/MyQueue</QueueUrl>
 *     </GetQueueUrlResult>
 *     <ResponseMetadata>
 *         <RequestId>552d6f30-4c8e-5b32-aaed-33408c7d6c38</RequestId>
 *     </ResponseMetadata>
 * </GetQueueUrlResponse>
 */
namespace AwsMock::Dto::SQS {

    struct GetQueueUrlResponse {

      /**
       * Name of the queue
       */
      std::string queueUrl;

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml() {

          // Root
          Poco::XML::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;
          Poco::XML::AutoPtr<Poco::XML::Element> pRoot = pDoc->createElement("GetQueueUrlResponse");
          pDoc->appendChild(pRoot);

          // CreateQueueResult
          Poco::XML::AutoPtr<Poco::XML::Element> pQueueUelResult = pDoc->createElement("GetQueueUrlResult");
          pRoot->appendChild(pQueueUelResult);

          Poco::XML::AutoPtr<Poco::XML::Element> pQueueUrl = pDoc->createElement("QueueUrl");
          pQueueUelResult->appendChild(pQueueUrl);
          Poco::XML::AutoPtr<Poco::XML::Text> pQueueUrlText = pDoc->createTextNode(queueUrl);
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
       * Convert to a JSON string
       *
       * @return JSON string
       */
      std::string ToJson() {

          try {
              Poco::JSON::Object rootJson;
              rootJson.set("QueueUrl", queueUrl);

              std::ostringstream os;
              rootJson.stringify(os);
              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
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
      friend std::ostream &operator<<(std::ostream &os, const GetQueueUrlResponse &r) {
          os << "GetQueueUrlRequest={queueUrl='" << r.queueUrl << "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_GETQUEUEURLRESPONSE_H
