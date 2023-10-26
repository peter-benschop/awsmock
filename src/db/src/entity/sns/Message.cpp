//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sns/Message.h>

namespace AwsMock::Database::Entity::SNS {

  view_or_value<view, value> Message::ToDocument() const {

    auto messageAttributesDoc = bsoncxx::builder::basic::array{};
    for (const auto &attribute : attributes) {
      messageAttributesDoc.append(attribute.ToDocument());
    }

    view_or_value<view, value> messageDoc = make_document(
        kvp("region", region),
        kvp("topicArn", topicArn),
        kvp("targetArn", targetArn),
        kvp("message", message),
        kvp("messageId", messageId),
        kvp("status", MessageStatusToString(status)),
        kvp("attributes", messageAttributesDoc),
        kvp("reset", bsoncxx::types::b_date(std::chrono::milliseconds(0))),
        kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return messageDoc;
  }

  void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
    targetArn = bsoncxx::string::to_string(mResult.value()["targetArn"].get_string().value);
    message = bsoncxx::string::to_string(mResult.value()["message"].get_string().value);
    status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
    messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
    lastSend = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["reset"].get_date().value) / 1000));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    bsoncxx::array::view attributesView{mResult.value()["attributes"].get_array().value};
    for (bsoncxx::array::element attributeElement : attributesView) {
      MessageAttribute attribute{
          .attributeName=bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
          .attributeValue=bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value)
      };
      attributes.push_back(attribute);
    }
  }

  void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
    targetArn = bsoncxx::string::to_string(mResult.value()["targetArn"].get_string().value);
    message = bsoncxx::string::to_string(mResult.value()["message"].get_string().value);
    status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
    messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
    lastSend = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["reset"].get_date().value) / 1000));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    bsoncxx::array::view attributesView{mResult.value()["attributes"].get_array().value};
    for (bsoncxx::array::element attributeElement : attributesView) {
      MessageAttribute attribute{
          .attributeName=bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
          .attributeValue=bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value)
      };
      attributes.push_back(attribute);
    }
  }

  std::string Message::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Message &message) {
    os << "Message={oid='" + message.oid + "' topicArn: " + message.topicArn + "' targetArn='" + message.targetArn + "'message='" + message.message + "'messageId='" + message.messageId
        + "' reset='" + Poco::DateTimeFormatter().format(message.lastSend, Poco::DateTimeFormat::HTTP_FORMAT) + "' created='" +
        Poco::DateTimeFormatter().format(message.created, Poco::DateTimeFormat::HTTP_FORMAT) + "' modified='" +
        Poco::DateTimeFormatter().format(message.modified, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::SNS
