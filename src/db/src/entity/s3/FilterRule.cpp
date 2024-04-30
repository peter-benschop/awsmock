//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/FilterRule.h>

namespace AwsMock::Database::Entity::S3 {

    view_or_value<view, value> FilterRule::ToDocument() const {

        auto filterRuleDoc = bsoncxx::builder::basic::document{};
        filterRuleDoc.append(kvp("name", name));
        filterRuleDoc.append(kvp("value", value));

        return filterRuleDoc.extract();
    }

    void FilterRule::FromDocument(bsoncxx::document::element mResult) {

        name = bsoncxx::string::to_string(mResult["name"].get_string().value);
        value = bsoncxx::string::to_string(mResult["value"].get_string().value);
    }

    Poco::JSON::Object FilterRule::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("name", name);
        jsonObject.set("value", value);
        return jsonObject;
    }

    void FilterRule::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("name", jsonObject, name);
        Core::JsonUtils::GetJsonValueString("value", jsonObject, value);
    }

    std::string FilterRule::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const FilterRule &n) {
        os << "FilterRule=" << bsoncxx::to_json(n.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::S3
