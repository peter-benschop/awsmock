//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/ssm/Parameter.h>

namespace AwsMock::Database::Entity::SSM {

    view_or_value<view, value> Parameter::ToDocument() const {

        auto tagsDoc = bsoncxx::builder::basic::document{};
        if (!tags.empty()) {
            for (const auto &t: tags) {
                tagsDoc.append(kvp(t.first, t.second));
            }
        }

        view_or_value<view, value> userDocument = make_document(
                kvp("region", region),
                kvp("name", parameterName),
                kvp("value", parameterValue),
                kvp("type", type),
                kvp("description", description),
                kvp("tier", tier),
                kvp("version", version),
                kvp("arn", arn),
                kvp("tags", tagsDoc),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));
        return userDocument;
    }

    void Parameter::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        parameterName = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
        parameterValue = bsoncxx::string::to_string(mResult.value()["value"].get_string().value);
        type = bsoncxx::string::to_string(mResult.value()["type"].get_string().value);
        description = bsoncxx::string::to_string(mResult.value()["description"].get_string().value);
        tier = bsoncxx::string::to_string(mResult.value()["tier"].get_string().value);
        version = mResult.value()["version"].get_int32().value;
        arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            if (mResult.value().find("tags") != mResult.value().end()) {
                bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
                for (const bsoncxx::document::element &tagElement: tagsView) {
                    std::string key = bsoncxx::string::to_string(tagElement.key());
                    std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                    tags.emplace(key, value);
                }
            }
        }
    }


    Poco::JSON::Object Parameter::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("arn", arn);
        jsonObject.set("name", parameterName);
        jsonObject.set("value", parameterValue);
        jsonObject.set("type", type);
        jsonObject.set("description", description);
        jsonObject.set("tier", tier);
        jsonObject.set("version", version);
        jsonObject.set("created", Core::DateTimeUtils::ToISO8601(created));
        jsonObject.set("modified", Core::DateTimeUtils::ToISO8601(modified));

        return jsonObject;
    }

    std::string Parameter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Parameter &u) {
        os << "Parameter=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::SSM