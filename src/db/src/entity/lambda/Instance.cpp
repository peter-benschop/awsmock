//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Instance.h>

namespace AwsMock::Database::Entity::Lambda {

    void Instance::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {
        id = bsoncxx::string::to_string(mResult.value()["id"].get_string().value);
        containerId = bsoncxx::string::to_string(mResult.value()["containerId"].get_string().value);
        hostPort = mResult.value()["hostPort"].get_int32().value;
        status = LambdaInstanceStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
    }

    view_or_value<view, value> Instance::ToDocument() const {

        bsoncxx::builder::basic::document instanceDoc{};

        instanceDoc.append(kvp("id", id));
        instanceDoc.append(kvp("containerId", containerId));
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