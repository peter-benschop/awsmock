//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_TRANSFER_H
#define AWSMOCK_DB_ENTITY_TRANSFER_H

// C++ includes
#include <chrono>
#include <map>
#include <string>
#include <vector>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>


// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/transfer/User.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::Transfer {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    enum ServerState {
        OFFLINE,
        ONLINE,
        STARTING,
        STOPPING,
        START_FAILED,
        STOP_FAILED
    };

    static std::map<ServerState, std::string> ServerStateNames{
            {OFFLINE, "OFFLINE"},
            {ONLINE, "ONLINE"},
            {STARTING, "STARTING"},
            {STOPPING, "STOPPING"},
            {START_FAILED, "START_FAILED"},
            {STOP_FAILED, "STOP_FAILED"}};

    static std::string ServerStateToString(const ServerState &serverState) {
        return ServerStateNames[serverState];
    }

    static ServerState ServerStateFromString(const std::string &serverState) {
        for (auto &[fst, snd]: ServerStateNames) {
            if (snd == serverState) {
                return fst;
            }
        }
        return OFFLINE;
    }

    /**
     * Transfer manager server entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
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
        ServerState state = OFFLINE;

        /**
         * Concurrency, number of FTP manager threads
         */
        int concurrency = 8;

        /**
         * Port
         */
        int port = 21;

        /**
         * Listen address
         */
        std::string listenAddress = "0.0.0.0";

        /**
         * Last transfer manager StartServer
         */
        system_clock::time_point lastStarted;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified;

        /**
         * @brief Checks whether a user exists already.
         *
         * @param userName name of the user
         * @return true if transfer manager with the given user exists.
         */
        bool HasUser(const std::string &userName);

        /**
         * @brief Return a user.
         *
         * @param userName name of the user
         * @return true if transfer manager with the given user exists.
         */
        User GetUser(const std::string &userName);

        /**
         * @brief Checks whether a protocol exists already.
         *
         * @param p name of the protocol
         * @return true if transfer manager with the given protocol exists.
         */
        bool HasProtocol(const std::string &p);

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        void FromDocument(const std::optional<view> &mResult);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts the entity to a JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param m transfer
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Transfer &m);
    };

    typedef Transfer Transfer;
    typedef std::vector<Transfer> TransferList;

}// namespace AwsMock::Database::Entity::Transfer

#endif// AWSMOCK_DB_ENTITY_TRANSFER_H
