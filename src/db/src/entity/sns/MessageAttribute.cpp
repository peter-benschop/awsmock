//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sns/MessageAttribute.h>

namespace AwsMock::Database::Entity::SNS {

  view_or_value<view, value> MessageAttribute::ToDocument() const {

    view_or_value<view, value> messageAttributeDoc = make_document(
        kvp("name", attributeName),
        kvp("value", attributeValue));

    return messageAttributeDoc;
  }

  Poco::JSON::Object MessageAttribute::ToJsonObject() const {

    Poco::JSON::Object jsonObject;
    jsonObject.set("name", attributeName);
    jsonObject.set("value", attributeValue);
    return jsonObject;

  }

  std::string MessageAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const MessageAttribute &m) {
    os << "MessageAttribute=" << bsoncxx::to_json(m.ToDocument());
    return os;
  }

} // namespace AwsMock::Database::Entity::SNS
