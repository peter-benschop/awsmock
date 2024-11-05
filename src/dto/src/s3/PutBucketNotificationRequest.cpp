//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationRequest.h>

namespace AwsMock::Dto::S3 {

    //    void PutBucketNotificationRequest::FromXML(const std::string &xmlString) {
    //
    //        Poco::XML::DOMParser parser;
    //        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);
    //
    //        Poco::XML::Node *cloudNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration");
    //        if (cloudNode) {
    //            Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Id");
    //            notificationId = idNode->innerText();
    //
    //            Poco::XML::Node *functionNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/CloudFunction");
    //            lambdaArn = functionNode->innerText();
    //
    //            Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Event");
    //            event = eventNode->innerText();
    //        }
    //
    //        Poco::XML::Node *queueNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration");
    //        if (queueNode) {
    //            Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Id");
    //            notificationId = idNode->innerText();
    //
    //            Poco::XML::Node *queueArnNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Queue");
    //            queueArn = queueArnNode->innerText();
    //
    //            Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Event");
    //            event = eventNode->innerText();
    //        }
    //    }
    //
    //    std::string PutBucketNotificationRequest::ToString() const {
    //        std::stringstream ss;
    //        ss << (*this);
    //        return ss.str();
    //    }
    //
    //    std::ostream &operator<<(std::ostream &os, const PutBucketNotificationRequest &r) {
    //        os << "PutBucketNotificationRequest={region='" + r.region + "' bucket='" + r.bucket + "' queueArn='" + r.queueArn + "' lambdaArn='" + r.lambdaArn +
    //                        "' event='" + r.event + "'userPoolId='" + r.notificationId + "'}";
    //        return os;
    //    }

}// namespace AwsMock::Dto::S3
