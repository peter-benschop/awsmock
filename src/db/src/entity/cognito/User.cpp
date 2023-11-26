//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/User.h>

namespace AwsMock::Database::Entity::Cognito {

  view_or_value<view, value> User::ToDocument() const {

    auto userAttributesDoc = bsoncxx::builder::basic::array{};
    for (const auto &attribute : attributes) {
      userAttributesDoc.append(make_document(kvp(attribute.name, attribute.value)));
    }

    view_or_value<view, value> userDocument = make_document(
        kvp("userName", userName),
        kvp("enabled", enabled),
        kvp("userStatus", Entity::Cognito::UserStatusToString(userStatus)),
        kvp("attributes", userAttributesDoc),
        kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));
    return userDocument;

  }

  void User::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    userName = bsoncxx::string::to_string(mResult.value()["userName"].get_string().value);
    enabled = mResult.value()["enabled"].get_bool().value;
    userStatus = Entity::Cognito::UserStatusFromString(bsoncxx::string::to_string(mResult.value()["userStatus"].get_string().value));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    bsoncxx::array::view attributesView{mResult.value()["attributes"].get_array().value};
    for (bsoncxx::array::element attributeElement : attributesView) {
      Attribute attribute{
          .name=bsoncxx::string::to_string(attributeElement["name"].get_string().value),
          .value=bsoncxx::string::to_string(attributeElement["value"].get_string().value)
      };
      attributes.push_back(attribute);
    }
  }

  std::string User::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const User &u) {
    os << "User={oid='" << u.oid << "', userName='" << u.userName << "', enabled='" << u.enabled << "', userStatus='" << Entity::Cognito::UserStatusToString(u.userStatus) << "', attributes={";
    for(const auto &attribute:u.attributes) {
      os << attribute.name << "'" << attribute.value << "', ";
    }
    os << "\b\b" << "}";
    os << ", created='" << Poco::DateTimeFormatter().format(u.created, Poco::DateTimeFormat::HTTP_FORMAT) << "', modified='" << Poco::DateTimeFormatter().format(u.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
    return os;
  }
}