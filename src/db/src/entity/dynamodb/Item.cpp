//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/Item.h>

namespace AwsMock::Database::Entity::DynamoDb {

    view_or_value<view, value> Item::ToDocument() const {

        try {

            auto attributesDoc = document{};
            for (const auto &[fst, snd]: attributes) {
                attributesDoc.append(kvp(fst, snd.ToDocument()));
            }

            auto itemDoc = document{};
            itemDoc.append(
                    kvp("region", region),
                    kvp("tableName", tableName),
                    kvp("attributes", attributesDoc),
                    kvp("created", bsoncxx::types::b_date(created)),
                    kvp("modified", bsoncxx::types::b_date(modified)));

            return itemDoc.extract();

        } catch (const std::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Item Item::FromDocument(const optional<view> &mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        tableName = Core::Bson::BsonUtils::GetStringValue(mResult, "tableName");
        created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
        modified = Core::Bson::BsonUtils::GetDateValue(mResult, "modified");
        return *this;
    }

    std::string Item::ToJson() const {
        return to_json(ToDocument());
    }

    std::string Item::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Item &d) {
        os << "Item=" << to_json(d.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::DynamoDb