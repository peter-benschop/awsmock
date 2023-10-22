//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/service/Service.h>

namespace AwsMock::Database::Entity::Service {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  /*Service::Service(const mongocxx::stdx::optional<bsoncxx::document::value> &mResult) : status(ServiceStatus::UNKNOWN) {
    FromDocument(mResult);
  }*/

  view_or_value<view, value> Service::ToDocument() const {

    view_or_value<view, value> objectDoc = make_document(
        kvp("name", name),
        kvp("status", ServiceStatusToString(status)),
        kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return objectDoc;
  }

  void Service::FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    status = ServiceStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
  }

  std::string Service::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Service &s) {
    os << "Service={id='" << s.oid << "', name='" << s.name << "', status='" << ServiceStatusToString(s.status) << "', created=" << Poco::DateTimeFormatter().format(s.created, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', modified=" << Poco::DateTimeFormatter().format(s.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "}";
    return os;
  }

} // AwsMock::Database::Entity::Service