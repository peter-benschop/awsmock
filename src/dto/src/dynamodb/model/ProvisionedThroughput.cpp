//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/dto/dynamodb/model/ProvisionedThroughput.h"

namespace AwsMock::Dto::DynamoDb {


    Poco::JSON::Object ProvisionedThroughput::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("ReadCapacityUnits", readCapacityUnits);
        jsonObject.set("WriteCapacityUnits", writeCapacityUnits);
        jsonObject.set("LastDecreaseDateTime", lastDecreaseDateTime);
        jsonObject.set("LastIncreaseDateTime", lastIncreaseDateTime);
        jsonObject.set("NumberOfDecreasesToday", numberOfDecreasesToday);
        return jsonObject;
    }

    std::string ProvisionedThroughput::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    void ProvisionedThroughput::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {
        Core::JsonUtils::GetJsonValueInt("ReadCapacityUnits", jsonObject, readCapacityUnits);
        Core::JsonUtils::GetJsonValueInt("WriteCapacityUnits", jsonObject, writeCapacityUnits);
        Core::JsonUtils::GetJsonValueDate("LastDecreaseDateTime", jsonObject, lastDecreaseDateTime);
        Core::JsonUtils::GetJsonValueDate("LastIncreaseDateTime", jsonObject, lastIncreaseDateTime);
        Core::JsonUtils::GetJsonValueLong("NumberOfDecreasesToday", jsonObject, numberOfDecreasesToday);
    }

    std::string ProvisionedThroughput::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ProvisionedThroughput &p) {
        os << "ProvisionedThroughput=" << p.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
