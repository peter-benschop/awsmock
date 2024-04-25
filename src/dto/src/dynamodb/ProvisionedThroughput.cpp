//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/dynamodb/ProvisionedThroughput.h>

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
