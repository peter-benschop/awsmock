//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DTO_S3_NOTIFICATIONCONFIGURATION_H
#define AWSMOCK_DTO_S3_NOTIFICATIONCONFIGURATION_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

    /**
     * Process the S3 notification configuration:
     *
     * <pre>
     * <NotificationConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
     *      <CloudFunctionConfiguration>
     *          <Id>1234567890123</Id>
     *          <CloudFunction>arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy</CloudFunction>
     *          <Event>s3:ObjectCreated:*</Event>
     *      </CloudFunctionConfiguration>
     * </NotificationConfiguration>
     * </pre>
     */
    struct PutBucketNotificationRequest {

      /**
       * Constructor
       *
       * @param xmlString XML string
       */
      explicit PutBucketNotificationRequest(const std::string &xmlString, const std::string &region, const std::string &bucket) {

          this->region = region;
          this->bucket = bucket;

          Poco::XML::DOMParser parser;
          Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

          Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Id");
          notificationId = std::stol(idNode->innerText());

          Poco::XML::Node *functionNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/CloudFunction");
          function = functionNode->innerText();

          Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Event");
          event = eventNode->innerText();
      }

      /**
       * Id
       */
      long notificationId = 0;

      /**
       * AWS region
       */
      std::string region;

      /**
       * AWS region
       */
      std::string bucket;

      /**
       * Function
       */
      std::string function;

      /**
       * Event
       */
      std::string event;

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
      friend std::ostream &operator<<(std::ostream &os, const PutBucketNotificationRequest &r) {
          os << "PutBucketNotificationRequest={id='" + std::to_string(r.notificationId) + "' function='" + r.function + "' event='" + r.event + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif // AWS_MOCK_DTO_INCLUDE_AWSMOCK_DTO_S3_NOTIFICATIONCONFIGURATION_H
