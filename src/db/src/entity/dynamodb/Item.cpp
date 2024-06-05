//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/Item.h>

namespace AwsMock::Database::Entity::DynamoDb {

    view_or_value<view, value> Item::ToDocument() const {

        try {

            auto attributesDoc = bsoncxx::builder::basic::document{};
            for (const auto &attribute: attributes) {
                attributesDoc.append(kvp(attribute.first, attribute.second.ToDocument()));
            }

            auto itemDoc = bsoncxx::builder::basic::document{};
            itemDoc.append(
                    kvp("region", region),
                    kvp("tableName", tableName),
                    kvp("attributes", attributesDoc),
                    kvp("created", bsoncxx::types::b_date(created)),
                    kvp("modified", bsoncxx::types::b_date(modified)));

            return itemDoc.extract();

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Entity::DynamoDb::Item Item::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        tableName = bsoncxx::string::to_string(mResult.value()["tableName"].get_string().value);
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);
        return *this;
    }

    Poco::JSON::Object Item::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("tableName", tableName);


        return jsonObject;
    }

    std::string Item::ToJson() const {
        return bsoncxx::to_json(ToDocument());
    }

    std::string Item::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Item &i) {
        os << "Item=" << bsoncxx::to_json(i.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::DynamoDb