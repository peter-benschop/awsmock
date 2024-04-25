//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_TRANSFERMEMORYDB_H
#define AWSMOCK_REPOSITORY_TRANSFERMEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/transfer/Transfer.h>
#include <awsmock/entity/transfer/User.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * Transfer manager in-memory database.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class TransferMemoryDb {

      public:
        /**
         * Constructor
         */
        TransferMemoryDb() = default;

        /**
         * Singleton instance
         */
        static TransferMemoryDb &instance() {
            static Poco::SingletonHolder<TransferMemoryDb> sh;
            return *sh.get();
        }

        /**
         * Check existence of transfer servers
         *
         * @param region AWS region name
         * @param serverId AWS server ID
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &region, const std::string &serverId);

        /**
         * Check existence of transfer servers
         *
         * @param transfer AWS transfer
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const Entity::Transfer::Transfer &transfer);

        /**
         * Check existence of transfer servers
         *
         * @param serverId AWS server ID
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &serverId);

        /**
         * Check existence of transfer servers by protocol
         *
         * @param region AWS region name
         * @param protocols list of protocols
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &region, const std::vector<std::string> &protocols);

        /**
         * Returns a list of transfer manager.
         *
         * @param region AWS region name
         * @return list of transfer manager
         */
        std::vector<Entity::Transfer::Transfer> ListServers(const std::string &region);

        /**
         * Create a new transfer servers
         *
         * @param transfer transfer entity
         * @return created transfer entity.
         */
        Entity::Transfer::Transfer CreateTransfer(const Entity::Transfer::Transfer &transfer);

        /**
         * Updates an existing transfer manager
         *
         * @param transfer transfer entity
         * @return updated transfer entity.
         */
        Entity::Transfer::Transfer UpdateTransfer(const Entity::Transfer::Transfer &transfer);

        /**
         * Returns a transfer manager entity by primary key
         *
         * @param oid transfer manager primary key
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferById(const std::string &oid);

        /**
         * Returns a transfer manager entity by manager ID
         *
         * @param serverId transfer manager ID
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferByServerId(const std::string &serverId);

        /**
         * Returns a transfer manager entity by ARN
         *
         * @param arn transfer manager ARN
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferByArn(const std::string &arn);

        /**
         * Returns the total number of servers.
         *
         * @param region AWS region name
         * @return total number of transfer server
         */
        long CountServers(const std::string &region = {});

        /**
         * Deletes an existing transfer manager
         *
         * @param serverId transfer server ID
         * @throws DatabaseException
         */
        void DeleteTransfer(const std::string &serverId);

        /**
         * Deletes all existing transfer server
         *
         * @throws DatabaseException
         */
        void DeleteAllTransfers();

      private:
        /**
         * Transfer server map, when running without database
         */
        std::map<std::string, Entity::Transfer::Transfer> _transfers;

        /**
         * Transfer user map, when running without database
         */
        std::map<std::string, Entity::Transfer::User> _users;

        /**
         * Transfer mutex
         */
        Poco::Mutex _transferMutex;

        /**
         * User mutex
         */
        Poco::Mutex _userMutex;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_TRANSFERMEMORYDB_H
