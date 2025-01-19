//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/dynamodb/model/ItemCounter.h>

namespace AwsMock::Dto::DynamoDb {

    view_or_value<view, value> ItemCounter::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "tableName", tableName);
            Core::Bson::BsonUtils::SetLongValue(document, "size", size);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);

            document.append(kvp("item", item.ToDocument()));

            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ItemCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ItemCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ItemCounter &c) {
        os << "TableCounter=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
