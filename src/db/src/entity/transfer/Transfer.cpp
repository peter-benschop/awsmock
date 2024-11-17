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
                kvp("state", Entity::Transfer::ServerStateToString(state)),
                kvp("concurrency", concurrency),
                kvp("port", port),
                kvp("listenAddress", listenAddress),
                kvp("lastStarted", bsoncxx::types::b_date(lastStarted)),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

        return transferDoc;
    }

    void Transfer::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        serverId = Core::Bson::BsonUtils::GetStringValue(mResult, "serverId");
        arn = Core::Bson::BsonUtils::GetStringValue(mResult, "arn");
        state = Entity::Transfer::ServerStateFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "state"));
        concurrency = Core::Bson::BsonUtils::GetIntValue(mResult, "concurrency");
        port = mResult.value()["port"].get_int32().value;
        listenAddress = bsoncxx::string::to_string(mResult.value()["listenAddress"].get_string().value);
        lastStarted = bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date());
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());

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
                User user = {
                        .userName = bsoncxx::string::to_string(userElement["userName"].get_string().value),
                        .password = bsoncxx::string::to_string(userElement["password"].get_string().value),
                        .homeDirectory = bsoncxx::string::to_string(userElement["homeDirectory"].get_string().value),
                        .arn = bsoncxx::string::to_string(userElement["arn"].get_string().value)};
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
        jsonObject.set("lastStarted", Core::DateTimeUtils::ToISO8601(lastStarted));

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

    void Transfer::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueInt("port", jsonObject, port);
        Core::JsonUtils::GetJsonValueInt("concurrency", jsonObject, concurrency);
        Core::JsonUtils::GetJsonValueString("serverId", jsonObject, serverId);
        Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
        Core::JsonUtils::GetJsonValueString("listenAddress", jsonObject, listenAddress);
        Core::JsonUtils::GetJsonValueDate("lastStarted", jsonObject, lastStarted);
        std::string stateStr;
        Core::JsonUtils::GetJsonValueString("state", jsonObject, stateStr);
        state = ServerStateFromString(stateStr);

        // Users
        if (jsonObject->has("users")) {
            Poco::JSON::Array::Ptr jsonUsersArray = jsonObject->getArray("users");
            for (int i = 0; i < jsonUsersArray->size(); i++) {
                User user;
                user.FromJsonObject(jsonUsersArray->getObject(i));
                users.emplace_back(user);
            }
        }

        if (jsonObject->has("protocols")) {
            Poco::JSON::Array::Ptr jsonProtocolsArray = jsonObject->getArray("protocols");
            for (int i = 0; i < jsonProtocolsArray->size(); i++) {
                protocols.emplace_back(jsonProtocolsArray->getElement<std::string>(i));
            }
        }
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
