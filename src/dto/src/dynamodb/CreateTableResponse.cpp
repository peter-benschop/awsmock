//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/dynamodb/CreateTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string CreateTableResponse::ToJson() const {

        try {

            bsoncxx::builder::basic::document document;

            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "TableClass", tableClass);
            Core::Bson::BsonUtils::SetStringValue(document, "TableName", tableName);

            if (!tags.empty()) {
                bsoncxx::builder::basic::array jsonArray;
                for (const auto &[fst, snd]: tags) {
                    bsoncxx::builder::basic::document element;
                    Core::Bson::BsonUtils::SetStringValue(element, "Key", fst);
                    Core::Bson::BsonUtils::SetStringValue(element, "Value", snd);
                    jsonArray.append(element);
                }
                document.append(kvp("Tags", jsonArray));
            }

            if (!attributes.empty()) {
                bsoncxx::builder::basic::array jsonArray;
                for (const auto &[fst, snd]: attributes) {
                    bsoncxx::builder::basic::document element;
                    Core::Bson::BsonUtils::SetStringValue(element, "AttributeName", fst);
                    Core::Bson::BsonUtils::SetStringValue(element, "AttributeType", snd);
                    jsonArray.append(element);
                }
                document.append(kvp("AttributeDefinitions", jsonArray));
            }

            if (!keySchemas.empty()) {
                bsoncxx::builder::basic::array jsonArray;
                for (const auto &[fst, snd]: keySchemas) {
                    bsoncxx::builder::basic::document element;
                    Core::Bson::BsonUtils::SetStringValue(element, "AttributeName", fst);
                    Core::Bson::BsonUtils::SetStringValue(element, "KeyType", snd);
                    jsonArray.append(element);
                }
                document.append(kvp("KeySchema", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateTableResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTableResponse &r) {
        os << "CreateTableResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
