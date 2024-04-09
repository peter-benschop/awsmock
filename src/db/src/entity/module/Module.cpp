//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/module/Module.h>

namespace AwsMock::Database::Entity::Module {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  view_or_value<view, value> Module::ToDocument() const {

    view_or_value<view, value> objectDoc = make_document(
        kvp("name", name),
        kvp("executable", executable),
        kvp("port", port),
        kvp("state", ModuleStateToString(state)),
        kvp("status", ModuleStatusToString(status)),
        kvp("created",
            bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified",
            bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return objectDoc;
  }

  void Module::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    executable = bsoncxx::string::to_string(mResult.value()["executable"].get_string().value);
    port = mResult.value()["port"].get_int32().value;
    state = ModuleStateFromString(bsoncxx::string::to_string(mResult.value()["state"].get_string().value));
    status = ModuleStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
  }

  std::string Module::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Module &m) {
    os << "Service={id='" << m.oid << "', name='" << m.name << "', executable='" << m.executable << "', port=" << m.port
       << ", state='" << ModuleStateToString(m.state) << ", status='" << ModuleStatusToString(m.status)
       << "', created=" << Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', modified=" << Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "}";
    return os;
  }

} // AwsMock::Database::Entity::Service