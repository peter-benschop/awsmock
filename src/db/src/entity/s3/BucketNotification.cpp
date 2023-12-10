//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/BucketNotification.h>

namespace AwsMock::Database::Entity::S3 {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  view_or_value<view, value> BucketNotification::ToDocument() const {

    view_or_value<view, value> notificationDoc = make_document(
        kvp("notificationId", notificationId),
        kvp("event", event),
        kvp("queueArn", queueArn),
        kvp("lambdaArn", lambdaArn));

    return notificationDoc;
  }

  Poco::JSON::Object BucketNotification::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("notificationId", notificationId);
    jsonObject.set("event", event);
    jsonObject.set("queueArn", queueArn);
    jsonObject.set("lambdaArn", lambdaArn);
    return jsonObject;
  }

  std::string BucketNotification::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const BucketNotification &q) {
    os << "BucketNotification={notificationId='" + q.notificationId + "' queueArn='" + q.queueArn + "' lambdaArn='" + q.lambdaArn + "' event='" + q.event + "'}";
    return os;
  }
} // namespace AwsMock::Database::Entity::S3

