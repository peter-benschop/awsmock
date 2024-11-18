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
        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        groupName = Core::Bson::BsonUtils::GetStringValue(mResult, "groupName");
        userPoolId = Core::Bson::BsonUtils::GetStringValue(mResult, "userPoolId");
        description = Core::Bson::BsonUtils::GetStringValue(mResult, "description");
        roleArn = Core::Bson::BsonUtils::GetStringValue(mResult, "roleArn");
        precedence = Core::Bson::BsonUtils::GetIntValue(mResult, "precedence");
        created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
        modified = Core::Bson::BsonUtils::GetDateValue(mResult, "modified");
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