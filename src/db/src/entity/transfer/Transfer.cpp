//
// Created by vogje01 on 07/06/2023.
//

#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database::Entity::Transfer {

    bool Transfer::HasUser(const std::string &userName) {
        return std::ranges::find_if(users, [userName](const User &user) {
                   return user.userName == userName;
               }) != users.end();
    }

    bool Transfer::HasProtocol(const std::string &p) {
        return std::ranges::find_if(protocols, [p](const std::string &protocol) {
                   return protocol == p;
               }) != protocols.end();
    }

    User Transfer::GetUser(const std::string &userName) {

        const auto it = std::ranges::find_if(users, [userName](const User &user) {
            return user.userName == userName;
        });
        if (it != users.end()) {
            return *it;
        }
        return {};
    }

    view_or_value<view, value> Transfer::ToDocument() const {

        auto protocolsDoc = array{};
        for (const auto &protocol: protocols) {
            protocolsDoc.append(protocol);
        }

        auto usersDoc = array{};
        for (const auto &user: users) {
            usersDoc.append(user.ToDocument());
        }

        view_or_value<view, value> transferDoc = make_document(
                kvp("region", region),
                kvp("serverId", serverId),
                kvp("arn", arn),
                kvp("protocols", protocolsDoc),
                kvp("users", usersDoc),
                kvp("state", ServerStateToString(state)),
                kvp("concurrency", concurrency),
                kvp("port", port),
                kvp("listenAddress", listenAddress),
                kvp("lastStarted", bsoncxx::types::b_date(lastStarted)),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

        return transferDoc;
    }

    void Transfer::FromDocument(const std::optional<view> &mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        serverId = Core::Bson::BsonUtils::GetStringValue(mResult, "serverId");
        arn = Core::Bson::BsonUtils::GetStringValue(mResult, "arn");
        state = ServerStateFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "state"));
        concurrency = Core::Bson::BsonUtils::GetIntValue(mResult, "concurrency");
        port = mResult.value()["port"].get_int32().value;
        listenAddress = bsoncxx::string::to_string(mResult.value()["listenAddress"].get_string().value);
        lastStarted = bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date());
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());

        // Protocols
        if (mResult.value().find("protocols") != mResult.value().end()) {
            for (auto [value] = mResult.value()["protocols"].get_array(); auto &p: value) {
                protocols.emplace_back(bsoncxx::string::to_string(p.get_string().value));
            }
        }

        // Users
        if (mResult.value().find("users") != mResult.value().end()) {
            for (const bsoncxx::array::view usersView{mResult.value()["users"].get_array().value}; const bsoncxx::array::element &userElement: usersView) {
                User user = {
                        .userName = bsoncxx::string::to_string(userElement["userName"].get_string().value),
                        .password = bsoncxx::string::to_string(userElement["password"].get_string().value),
                        .homeDirectory = bsoncxx::string::to_string(userElement["homeDirectory"].get_string().value),
                        .arn = bsoncxx::string::to_string(userElement["arn"].get_string().value)};
                users.push_back(user);
            }
        }
    }

    std::string Transfer::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Transfer &t) {
        os << "Transfer=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Transfer
