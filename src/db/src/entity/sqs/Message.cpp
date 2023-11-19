//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Database::Entity::SQS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  view_or_value<view, value> Message::ToDocument() const {

    auto messageAttributesDoc = bsoncxx::builder::basic::array{};
    for (const auto &attribute : attributes) {
      messageAttributesDoc.append(attribute.ToDocument());
    }

    view_or_value<view, value> messageDoc = make_document(
        kvp("region", region),
        kvp("queueUrl", queueUrl),
        kvp("body", body),
        kvp("status", MessageStatusToString(status)),
        kvp("retries", retries),
        kvp("messageId", messageId),
        kvp("receiptHandle", receiptHandle),
        kvp("md5Body", md5Body),
        kvp("md5Attr", md5Attr),
        kvp("attributes", messageAttributesDoc),
        kvp("reset", bsoncxx::types::b_date(std::chrono::milliseconds(reset.timestamp().epochMicroseconds() / 1000))),
        kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return messageDoc;
  }

  void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    queueUrl = bsoncxx::string::to_string(mResult.value()["queueUrl"].get_string().value);
    body = bsoncxx::string::to_string(mResult.value()["body"].get_string().value);
    status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
    retries = mResult.value()["retries"].get_int32().value;
    messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
    receiptHandle = bsoncxx::string::to_string(mResult.value()["receiptHandle"].get_string().value);
    md5Body = bsoncxx::string::to_string(mResult.value()["md5Body"].get_string().value);
    md5Attr = bsoncxx::string::to_string(mResult.value()["md5Attr"].get_string().value);
    reset = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["reset"].get_date().value) / 1000));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    bsoncxx::array::view attributesView{mResult.value()["attributes"].get_array().value};
    for (bsoncxx::array::element attributeElement : attributesView) {
      MessageAttribute attribute{
          .attributeName=bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
          .attributeValue=bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value),
          .attributeType=Database::Entity::SQS::MessageAttributeTypeFromString(bsoncxx::string::to_string(attributeElement["attributeType"].get_string().value))
      };
      attributes.push_back(attribute);
    }
  }

  std::string Message::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Message &m) {
    os << "Message={oid='" << m.oid << "', queueUrl='" << m.queueUrl << "', body='" << m.body << "', status='" << MessageStatusToString(m.status) << "' ,reset='" << Poco::DateTimeFormatter().format(m.reset, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', retries=" << m.retries << ", messageId='" << m.messageId << "', receiptHandle='" << m.receiptHandle << "', md5body='" << m.md5Body << "', md5Attr='" << m.md5Attr << "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::S3
