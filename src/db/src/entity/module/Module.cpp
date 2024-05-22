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
                kvp("port", port),
                kvp("state", ModuleStateToString(state)),
                kvp("status", ModuleStatusToString(status)),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return objectDoc;
    }

    void Module::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
        port = mResult.value()["port"].get_int32().value;
        state = ModuleStateFromString(bsoncxx::string::to_string(mResult.value()["state"].get_string().value));
        status = ModuleStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
        created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date().value));
        modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value));
    }

    std::string Module::ToJson() const {
        return bsoncxx::to_json(ToDocument());
    }

    std::string Module::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Module &m) {
        os << "Module=" << bsoncxx::to_json(m.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::Module