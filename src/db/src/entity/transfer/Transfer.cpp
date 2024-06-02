//
// Created by vogje01 on 07/06/2023.
//

#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database::Entity::Transfer {

    bool Transfer::HasUser(const std::string &userName) {
        return find_if(users.begin(), users.end(), [userName](const User &user) {
                   return user.userName == userName;
               }) != users.end();
    }

    bool Transfer::HasProtocol(const std::string &p) {
        return find_if(protocols.begin(), protocols.end(), [p](const std::string &protocol) {
                   return protocol == p;
               }) != protocols.end();
    }

    view_or_value<view, value> Transfer::ToDocument() const {

        auto protocolsDoc = bsoncxx::builder::basic::array{};
        for (const auto &protocol: protocols) {
            protocolsDoc.append(protocol);
        }

        auto usersDoc = bsoncxx::builder::basic::array{};
        for (const auto &user: users) {
            usersDoc.append(user.ToDocument());
        }

        view_or_value<view, value> transferDoc = make_document(
                kvp("region", region),
                kvp("serverId", serverId),
                kvp("arn", arn),
                kvp("protocols", protocolsDoc),
                kvp("users", usersDoc),
                kvp("state", state),
                kvp("concurrency", concurrency),
                kvp("port", port),
                kvp("listenAddress", listenAddress),
                kvp("lastStarted", MongoUtils::ToBson(lastStarted)),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return transferDoc;
    }

    void Transfer::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        serverId = bsoncxx::string::to_string(mResult.value()["serverId"].get_string().value);
        arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
        state = bsoncxx::string::to_string(mResult.value()["state"].get_string().value);
        concurrency = mResult.value()["concurrency"].get_int32().value;
        port = mResult.value()["port"].get_int32().value;
        listenAddress = bsoncxx::string::to_string(mResult.value()["listenAddress"].get_string().value);
        lastStarted = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date()));
        created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
        modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

        // Protocols
        if (mResult.value().find("protocols") != mResult.value().end()) {
            auto protocolsDoc = mResult.value()["protocols"].get_array();
            for (auto &p: protocolsDoc.value) {
                protocols.emplace_back(bsoncxx::string::to_string(p.get_string().value));
            }
        }

        // Users
        if (mResult.value().find("users") != mResult.value().end()) {
            bsoncxx::array::view usersView{mResult.value()["users"].get_array().value};
            for (const bsoncxx::array::element &userElement: usersView) {
                User user{
                        .userName = bsoncxx::string::to_string(userElement["userName"].get_string().value),
                        .password = bsoncxx::string::to_string(userElement["password"].get_string().value),
                        .homeDirectory = bsoncxx::string::to_string(userElement["homeDirectory"].get_string().value)};
                users.push_back(user);
            }
        }
    }

    Poco::JSON::Object Transfer::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("serverId", serverId);
        jsonObject.set("arn", arn);
        jsonObject.set("state", state);
        jsonObject.set("concurrency", concurrency);
        jsonObject.set("port", port);
        jsonObject.set("listenAddress", listenAddress);
        jsonObject.set("lastStarted", Poco::DateTimeFormatter::format(lastStarted, Poco::DateTimeFormat::ISO8601_FORMAT));

        if (!protocols.empty()) {
            Poco::JSON::Array jsonProtocolsArray;
            for (const auto &protocol: protocols) {
                jsonProtocolsArray.add(protocol);
            }
            jsonObject.set("protocols", jsonProtocolsArray);
        }

        if (!users.empty()) {
            Poco::JSON::Array jsonUsersArray;
            for (const auto &user: users) {
                jsonUsersArray.add(user.ToJsonObject());
            }
            jsonObject.set("users", jsonUsersArray);
        }

        return jsonObject;
    }

    std::string Transfer::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    /**
     * Stream provider.
     *
     * @return output stream
     */
    std::ostream &operator<<(std::ostream &os, const Transfer &t) {
        os << "Transfer=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Transfer
