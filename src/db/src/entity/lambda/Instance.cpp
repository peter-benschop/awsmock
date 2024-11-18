//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Instance.h>

namespace AwsMock::Database::Entity::Lambda {

    void Instance::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        id = Core::Bson::BsonUtils::GetStringValue(mResult, "id");
        containerId = Core::Bson::BsonUtils::GetStringValue(mResult, "containerId");
        containerName = Core::Bson::BsonUtils::GetStringValue(mResult, "containerName");
        hostPort = Core::Bson::BsonUtils::GetIntValue(mResult, "hostPort");
        status = LambdaInstanceStatusFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "status"));
        created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
    }

    view_or_value<view, value> Instance::ToDocument() const {

        bsoncxx::builder::basic::document instanceDoc{};

        instanceDoc.append(kvp("id", id));
        instanceDoc.append(kvp("containerId", containerId));
        instanceDoc.append(kvp("containerName", containerName));
        instanceDoc.append(kvp("hostPort", hostPort));
        instanceDoc.append(kvp("status", LambdaInstanceStatusToString(status)));
        instanceDoc.append(kvp("created", bsoncxx::types::b_date(created)));

        return instanceDoc.extract();
    }

    Poco::JSON::Object Instance::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("id", id);
        jsonObject.set("status", LambdaInstanceStatusToString(status));
        return jsonObject;
    }

    [[nodiscard]] std::string Instance::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Instance &t) {
        os << "Instance=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda