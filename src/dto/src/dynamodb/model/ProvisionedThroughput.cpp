//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/dynamodb/model/ProvisionedThroughput.h>

namespace AwsMock::Dto::DynamoDb {

    view_or_value<view, value> ProvisionedThroughput::ToDocument() const {
        document document;
        Core::Bson::BsonUtils::SetIntValue(document, "ReadCapacityUnits", readCapacityUnits);
        Core::Bson::BsonUtils::SetIntValue(document, "WriteCapacityUnits", writeCapacityUnits);
        Core::Bson::BsonUtils::SetDateValue(document, "LastDecreaseDateTime", lastDecreaseDateTime);
        Core::Bson::BsonUtils::SetDateValue(document, "LastIncreaseDateTime", lastIncreaseDateTime);
        Core::Bson::BsonUtils::SetLongValue(document, "NumberOfDecreasesToday", numberOfDecreasesToday);
        return document.extract();
    }

    void ProvisionedThroughput::FromDocument(view_or_value<view, value> document) {
        readCapacityUnits = Core::Bson::BsonUtils::GetIntValue(document, "ReadCapacityUnits");
        writeCapacityUnits = Core::Bson::BsonUtils::GetIntValue(document, "WriteCapacityUnits");
        lastDecreaseDateTime = Core::Bson::BsonUtils::GetDateValue(document, "LastDecreaseDateTime");
        lastIncreaseDateTime = Core::Bson::BsonUtils::GetDateValue(document, "LastIncreaseDateTime");
        numberOfDecreasesToday = Core::Bson::BsonUtils::GetLongValue(document, "NumberOfDecreasesToday");
    }

    std::string ProvisionedThroughput::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string ProvisionedThroughput::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ProvisionedThroughput &p) {
        os << "ProvisionedThroughput=" << p.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
