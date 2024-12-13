//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/cognito/User.h>

namespace AwsMock::Database::Entity::Cognito {

    bool User::HasGroup(const std::string &userPoolId, const std::string &groupName) {

        return std::ranges::find_if(groups, [&userPoolId, &groupName](const Group &g) {
                   return g.userPoolId == userPoolId && g.groupName == groupName;
               }) != groups.end();
    }

    view_or_value<view, value> User::ToDocument() const {

        // Attributes
        auto userAttributesDoc = array{};
        for (const auto &[name, value]: userAttributes) {
            userAttributesDoc.append(make_document(kvp(name, value)));
        }

        // Groups
        auto groupsDoc = array{};
        for (const auto &group: groups) {
            groupsDoc.append(group.ToDocument());
        }

        view_or_value<view, value> userDocument = make_document(
                kvp("region", region),
                kvp("userName", userName),
                kvp("userPoolId", userPoolId),
                kvp("enabled", enabled),
                kvp("groups", groupsDoc),
                kvp("userStatus", Entity::Cognito::UserStatusToString(userStatus)),
                kvp("userAttributes", userAttributesDoc),
                kvp("confirmationCode", confirmationCode),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));
        return userDocument;
    }

    void User::FromDocument(const std::optional<view> &mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        userName = Core::Bson::BsonUtils::GetStringValue(mResult, "userName");
        userPoolId = Core::Bson::BsonUtils::GetStringValue(mResult, "userPoolId");
        enabled = Core::Bson::BsonUtils::GetBoolValue(mResult, "enabled");
        userStatus = UserStatusFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "userStatus"));
        confirmationCode = Core::Bson::BsonUtils::GetStringValue(mResult, "confirmationCode");
        created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
        modified = Core::Bson::BsonUtils::GetDateValue(mResult, "modified");

        // Attributes
        if (mResult.value().find("userAttributes") != mResult.value().end()) {
            for (const bsoncxx::array::view attributesView{mResult.value()["userAttributes"].get_array().value}; const bsoncxx::array::element &attributeElement: attributesView) {
                UserAttribute attribute{
                        .name = bsoncxx::string::to_string(attributeElement["name"].get_string().value),
                        .value = bsoncxx::string::to_string(attributeElement["value"].get_string().value)};
                userAttributes.push_back(attribute);
            }
        }
        // Groups
        if (mResult.value().find("groups") != mResult.value().end()) {
            for (const bsoncxx::array::view groupsView{mResult.value()["groups"].get_array().value}; const bsoncxx::array::element &groupElement: groupsView) {
                Group group;
                group.FromDocument(groupElement.get_document().view());
                groups.push_back(group);
            }
        }
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &u) {
        os << "User=" << to_json(u.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Cognito