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
        for (const auto &protocol : protocols) {
            protocolsDoc.append(protocol);
        }

        auto usersDoc = bsoncxx::builder::basic::array{};
        for (const auto &user : users) {
            usersDoc.append(make_document(kvp("userName", user.userName), kvp("password", user.password), kvp("homeDirectory", user.homeDirectory)));
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
            kvp("lastStarted", bsoncxx::types::b_date(std::chrono::milliseconds(lastStarted.timestamp().epochMicroseconds() / 1000))),
            kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
            kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

        return transferDoc;
    }

    void Transfer::FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        serverId = bsoncxx::string::to_string(mResult.value()["serverId"].get_string().value);
        arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
        state = bsoncxx::string::to_string(mResult.value()["state"].get_string().value);
        concurrency = mResult.value()["concurrency"].get_int32().value;
        port = mResult.value()["port"].get_int32().value;
        listenAddress = bsoncxx::string::to_string(mResult.value()["listenAddress"].get_string().value);
        lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
        created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
        modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

        auto protocolsDoc = mResult.value()["protocols"].get_array();
        for (auto &p : protocolsDoc.value) {
            protocols.emplace_back(bsoncxx::string::to_string(p.get_string().value));
        }

        bsoncxx::array::view usersView{mResult.value()["users"].get_array().value};
        for (bsoncxx::array::element userElement : usersView) {
            User user{
                .userName=bsoncxx::string::to_string(userElement["userName"].get_string().value),
                .password=bsoncxx::string::to_string(userElement["password"].get_string().value),
                .homeDirectory=bsoncxx::string::to_string(userElement["homeDirectory"].get_string().value)
            };
            users.push_back(user);
        }
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
        lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
        created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
        modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

        auto protocolsDoc = mResult.value()["protocols"].get_array();
        for (auto &p : protocolsDoc.value) {
            protocols.emplace_back(bsoncxx::string::to_string(p.get_string().value));
        }

        bsoncxx::array::view usersView{mResult.value()["users"].get_array().value};
        for (bsoncxx::array::element userElement : usersView) {
            User user{
                .userName=bsoncxx::string::to_string(userElement["userName"].get_string().value),
                .password=bsoncxx::string::to_string(userElement["password"].get_string().value),
                .homeDirectory=bsoncxx::string::to_string(userElement["homeDirectory"].get_string().value)
            };
            users.push_back(user);
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
    std::ostream &operator<<(std::ostream &os, const Transfer &m) {
        os << "Transfer={oid='" << m.oid << "', region='" << m.region << "', serverId='" << m.serverId << "', arn='" << m.arn << "', concurrently=" << m.concurrency
           << ", port=" << m.port << ", listenAddress='" << m.listenAddress <<
           "', lastStarted='" << Poco::DateTimeFormatter().format(m.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) <<
           "', created='" << Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
           "', modified='" << Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
        return os;
    }
}
