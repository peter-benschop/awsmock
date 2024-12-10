//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/ssm/Parameter.h>

namespace AwsMock::Database::Entity::SSM {

    view_or_value<view, value> Parameter::ToDocument() const {

        auto tagsDoc = document{};
        if (!tags.empty()) {
            for (const auto &[fst, snd]: tags) {
                tagsDoc.append(kvp(fst, snd));
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

    void Parameter::FromDocument(std::optional<bsoncxx::document::view> mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        parameterName = Core::Bson::BsonUtils::GetStringValue(mResult, "name");
        parameterValue = Core::Bson::BsonUtils::GetStringValue(mResult, "value");
        type = Core::Bson::BsonUtils::GetStringValue(mResult, "type");
        description = Core::Bson::BsonUtils::GetStringValue(mResult, "description");
        tier = Core::Bson::BsonUtils::GetStringValue(mResult, "tier");
        version = Core::Bson::BsonUtils::GetIntValue(mResult, "version");
        arn = Core::Bson::BsonUtils::GetStringValue(mResult, "arn");
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            if (mResult.value().find("tags") != mResult.value().end()) {
                for (const view tagsView = mResult.value()["tags"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
                    std::string key = bsoncxx::string::to_string(tagElement.key());
                    std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                    tags.emplace(key, value);
                }
            }
        }
    }

    std::string Parameter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Parameter &u) {
        os << "Parameter=" << to_json(u.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::SSM