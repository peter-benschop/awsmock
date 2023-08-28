//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_TRANSFER_H
#define AWSMOCK_DB_ENTITY_TRANSFER_H

// C++ includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Database::Entity::Transfer {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    enum ServerState {
      OFFLINE,
      ONLINE,
      STARTING,
      STOPPING,
      START_FAILED,
      STOP_FAILED
    };

    static std::map<ServerState,std::string> ServerStateNames{
        {ServerState::OFFLINE, "OFFLINE"},
        {ServerState::ONLINE, "ONLINE"},
        {ServerState::STARTING, "STARTING"},
        {ServerState::STOPPING, "STOPPING"},
        {ServerState::START_FAILED, "START_FAILED"},
        {ServerState::STOP_FAILED, "STOP_FAILED"}
    };

    static std::string ServerStateToString(const ServerState &serverState) {
        return ServerStateNames[serverState];
    }

    /*static ServerState ServerStateFromString(const std::string &serverState) {
        for(auto &it : ServerStateNames) {
            if(it.second == serverState) {
                return it.first;
            }
        }
        return ServerState::OFFLINE;
    }*/

    struct User {

      /**
       * User name
       */
      std::string userName;

      /**
       * Password
       */
      std::string password;

      /**
       * Home directory
       */
      std::string homeDirectory;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const User &m) {
          os << "User={userName='" << m.userName << "' password='" << m.password << "' homeDirectory='" << m.homeDirectory << "'}";
          return os;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(bsoncxx::document::view mResult) {

          for (auto &v : mResult) {
              userName = v["userName"].get_string().value.to_string();
              password = v["password"].get_string().value.to_string();
              homeDirectory = v["homeDirectory"].get_string().value.to_string();
          }
      }
    };

    struct Transfer {

      /**
       * ID
       */
      std::string oid;

      /**
       * AWS region name
       */
      std::string region;

      /**
       * ServerId
       */
      std::string serverId;

      /**
       * ARN
       */
      std::string arn;

      /**
       * Server protocols
       */
      std::vector<std::string> protocols;

      /**
       * Users
       */
      std::vector<User> users;

      /**
       * State
       */
      std::string state = ServerStateToString(ServerState::OFFLINE);

      /**
       * Last transfer server start
       */
      Poco::DateTime lastStarted;

      /**
       * Creation date
       */
      Poco::DateTime created = Poco::DateTime();

      /**
       * Last modification date
       */
      Poco::DateTime modified = Poco::DateTime();

      /**
       * Checks whether a user exists already.
       *
       * @param userName name of the user
       * @return true if transfer server with the given user exists.
       */
      bool HasUser(const std::string &userName) {
          return find_if(users.begin(), users.end(), [userName](const User &user) {
            return user.userName == userName;
          }) != users.end();
      }

      /**
       * Checks whether a protocol exists already.
       *
       * @param userName name of the user
       * @return true if transfer server with the given user exists.
       */
      bool HasProtocol(const std::string &p) {
          return find_if(protocols.begin(), protocols.end(), [p](const std::string &protocol) {
            return protocol == p;
          }) != protocols.end();
      }

      /**
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[nodiscard]] view_or_value<view, value> ToDocument() const {

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
              kvp("lastStarted", bsoncxx::types::b_date(std::chrono::milliseconds(lastStarted.timestamp().epochMicroseconds() / 1000))),
              kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
              kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

          return transferDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          serverId = mResult.value()["serverId"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          state = mResult.value()["state"].get_string().value.to_string();
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

          auto protocolsDoc = mResult.value()["protocols"].get_array();
          for (auto &p : protocolsDoc.value) {
              protocols.emplace_back(p.get_string().value.to_string());
          }

          bsoncxx::array::view usersView{mResult.value()["users"].get_array().value};
          for (bsoncxx::array::element userElement : usersView) {
              User user{
                  .userName=userElement["userName"].get_string().value.to_string(),
                  .password=userElement["password"].get_string().value.to_string(),
                  .homeDirectory=userElement["homeDirectory"].get_string().value.to_string()
              };
              users.push_back(user);
          }
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          serverId = mResult.value()["serverId"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          state = mResult.value()["state"].get_string().value.to_string();
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

          auto varDoc = mResult.value()["protocols"].get_array();
          for (auto &v : varDoc.value) {
              protocols.emplace_back(v.get_string().value.to_string());
          }

          bsoncxx::array::view usersView{mResult.value()["users"].get_array().value};
          for (bsoncxx::array::element userElement : usersView) {
              User user{
                  .userName=userElement["userName"].get_string().value.to_string(),
                  .password=userElement["password"].get_string().value.to_string(),
                  .homeDirectory=userElement["homeDirectory"].get_string().value.to_string()
              };
              users.push_back(user);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Transfer &m) {
          os << "Transfer={oid='" << m.oid << "' region='" << m.region << "' serverId='" << m.serverId << "' arn='" << m.arn <<
             "' lastStarted='" << Poco::DateTimeFormatter().format(m.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' created='" << Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' modified='" << Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
          return os;
      }

    };

    typedef struct Transfer Transfer;
    typedef std::vector<Transfer> TransferList;
}
#endif // AWSMOCK_DB_ENTITY_TRANSFER_H
