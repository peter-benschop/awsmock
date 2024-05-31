//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/Group.h>

namespace AwsMock::Database::Entity::Cognito {

    view_or_value<view, value> Group::ToDocument() const {

        view_or_value<view, value> userDocument = make_document(
                kvp("region", region),
                kvp("groupName", groupName),
                kvp("userPoolId", userPoolId),
                kvp("description", description),
                kvp("roleArn", roleArn),
                kvp("precedence", precedence),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));
        return userDocument;
    }

    void Group::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        // Could be null, in case the group is part of a user
        if (mResult.value().find("_id") != mResult.value().end()) {
            oid = mResult.value()["_id"].get_oid().value.to_string();
        }
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        groupName = bsoncxx::string::to_string(mResult.value()["groupName"].get_string().value);
        userPoolId = bsoncxx::string::to_string(mResult.value()["userPoolId"].get_string().value);
        description = bsoncxx::string::to_string(mResult.value()["description"].get_string().value);
        roleArn = bsoncxx::string::to_string(mResult.value()["roleArn"].get_string().value);
        precedence = mResult.value()["precedence"].get_int32().value;
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);
    }

    Poco::JSON::Object Group::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("groupName", groupName);
        jsonObject.set("userPoolId", userPoolId);
        jsonObject.set("description", description);
        jsonObject.set("roleArn", roleArn);
        jsonObject.set("precedence", precedence);

        return jsonObject;
    }

    void Group::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("userName", jsonObject, groupName);
        Core::JsonUtils::GetJsonValueString("userPoolId", jsonObject, userPoolId);
        Core::JsonUtils::GetJsonValueString("description", jsonObject, description);
        Core::JsonUtils::GetJsonValueString("roleArn", jsonObject, roleArn);
        Core::JsonUtils::GetJsonValueInt("precedence", jsonObject, precedence);
    }

    std::string Group::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Group &u) {
        os << "Group=" << bsoncxx::to_json(u.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Cognito