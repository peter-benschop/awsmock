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
      kvp("md5UserAttr", md5UserAttr),
      kvp("md5SystemAttr", md5SystemAttr),
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
    md5UserAttr = bsoncxx::string::to_string(mResult.value()["md5UserAttr"].get_string().value);
    md5SystemAttr = bsoncxx::string::to_string(mResult.value()["md5SystemAttr"].get_string().value);
    if(mResult.value()["reset"].type() != bsoncxx::type::k_null) {
      reset = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["reset"].get_date().value) / 1000));
    }
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    bsoncxx::array::view attributesView{mResult.value()["attributes"].get_array().value};
    for (bsoncxx::array::element attributeElement : attributesView) {
      MessageAttribute attribute{
        .attributeName=bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
        .attributeValue=bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value),
        .attributeType=Database::Entity::SQS::MessageAttributeTypeFromString(bsoncxx::string::to_string(attributeElement["attributeType"].get_string().value)),
        .systemAttribute = attributeElement["systemAttribute"].get_bool().value,
      };
      attributes.push_back(attribute);
    }
  }

  Poco::JSON::Object Message::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("region", region);
    jsonObject.set("queueUrl", queueUrl);
    jsonObject.set("body", body);
    jsonObject.set("status", MessageStatusToString(status));
    jsonObject.set("messageId", messageId);
    jsonObject.set("receiptHandle", receiptHandle);
    jsonObject.set("md5Body", md5Body);
    jsonObject.set("md5UserAttr", md5UserAttr);
    jsonObject.set("md5SystemAttr", md5SystemAttr);
    jsonObject.set("reset", Poco::DateTimeFormatter::format(reset, Poco::DateTimeFormat::ISO8601_FORMAT));

    // Attributes
    Poco::JSON::Array jsonAttributeArray;
    for (const auto &attribute : attributes) {
      if (!attribute.systemAttribute) {
        Poco::JSON::Object jsonAttributeObject;
        jsonAttributeObject.set("name", attribute.attributeName);
        jsonAttributeObject.set("value", attribute.attributeValue);
        jsonAttributeArray.add(jsonAttributeObject);
      }
    }
    jsonObject.set("userAttributes", jsonAttributeArray);

    return jsonObject;
  }

  void Message::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

    Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
    Core::JsonUtils::GetJsonValueString("queueUrl", jsonObject, queueUrl);
    Core::JsonUtils::GetJsonValueString("body", jsonObject, body);
    Core::JsonUtils::GetJsonValueString("messageId", jsonObject, messageId);
    Core::JsonUtils::GetJsonValueString("receiptHandle", jsonObject, receiptHandle);
    Core::JsonUtils::GetJsonValueString("md5Body", jsonObject, md5Body);
    Core::JsonUtils::GetJsonValueString("md5UserAttr", jsonObject, md5UserAttr);
    Core::JsonUtils::GetJsonValueString("md5SystemAttr", jsonObject, md5SystemAttr);
    Core::JsonUtils::GetJsonValueDate("reset", jsonObject, reset);
    std::string statusStr;
    Core::JsonUtils::GetJsonValueString("status", jsonObject, statusStr);
    status = MessageStatusFromString(statusStr);

    // Attributes
    Poco::JSON::Array::Ptr jsonAttributeArray = jsonObject->getArray("userAttributes");
    for (int i = 0; i < jsonAttributeArray->size(); i++) {
      MessageAttribute messageAttribute;
      Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
      Core::JsonUtils::GetJsonValueString("name", jsonAttributeObject, messageAttribute.attributeName);
      Core::JsonUtils::GetJsonValueString("value", jsonAttributeObject, messageAttribute.attributeValue);
      messageAttribute.systemAttribute = false;
      attributes.emplace_back(messageAttribute);
    }
  }

  std::string Message::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Message &m) {
    os << "Message={oid='" << m.oid << "', queueUrl='" << m.queueUrl << "', body='" << m.body << "', status='" << MessageStatusToString(m.status) << "' ,reset='" << Poco::DateTimeFormatter().format(m.reset, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', retries=" << m.retries << ", messageId='" << m.messageId << "', receiptHandle='" << m.receiptHandle << "', md5body='" << m.md5Body << "', md5UserAttr='" << m.md5UserAttr << "', md5SystemAttr='" << m.md5SystemAttr << "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::S3
