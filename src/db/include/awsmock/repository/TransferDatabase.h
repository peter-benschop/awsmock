//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_TRANSFER_DATABASE_H
#define AWSMOCK_REPOSITORY_TRANSFER_DATABASE_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/entity/transfer/Transfer.h>
#include <awsmock/memorydb/TransferMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * @brief Transfer manager MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TransferDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit TransferDatabase();

        /**
         * @brief Singleton instance
         */
        static TransferDatabase &instance() {
            static TransferDatabase transferDatabase;
            return transferDatabase;
        }

        /**
         * @brief Check existence of lambda
         *
         * @param region AWS region name
         * @param serverId AWS server ID
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &region, const std::string &serverId);

        /**
         * @brief Check existence of lambda
         *
         * @param transfer AWS transfer
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const Entity::Transfer::Transfer &transfer);

        /**
         * @brief Check existence of lambda
         *
         * @param transferName AWS transfer name
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &transferName);

        /**
         * @brief Check existence of lambda
         *
         * @param region AWS region name
         * @param protocols list of protocols
         * @return true if transfer manager already exists
         * @throws DatabaseException
         */
        bool TransferExists(const std::string &region, const std::vector<std::string> &protocols);

        /**
         * @brief Create a new lambda function
         *
         * @param lambda lambda entity
         * @return created lambda entity.
         */
        Entity::Transfer::Transfer CreateTransfer(const Entity::Transfer::Transfer &lambda);

        /**
         * @brief Updates an existing transfer manager
         *
         * @param lambda lambda entity
         * @return updated lambda entity.
         */
        Entity::Transfer::Transfer UpdateTransfer(const Entity::Transfer::Transfer &lambda);

        /**
         * @brief Created or updates an existing transfer manager
         *
         * @param lambda lambda entity
         * @return created or updated lambda entity.
         */
        Entity::Transfer::Transfer CreateOrUpdateTransfer(const Entity::Transfer::Transfer &lambda);

        /**
         * @brief Returns a transfer manager entity by primary key
         *
         * @param oid transfer manager primary key
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferById(bsoncxx::oid oid);

        /**
         * @brief Returns a transfer manager entity by primary key
         *
         * @param oid transfer manager primary key
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferById(const std::string &oid);

        /**
         * @brief Returns a transfer manager entity by manager ID
         *
         * @param serverId transfer manager ID
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferByServerId(const std::string &serverId);

        /**
         * @brief Returns a transfer manager entity by ARN
         *
         * @param arn transfer manager ARN
         * @return transfer manager entity
         * @throws DatabaseException
         */
        Entity::Transfer::Transfer GetTransferByArn(const std::string &arn);

        /**
         * @brief Returns a list of transfer manager.
         *
         * @param region AWS region name
         * @return list of transfer manager
         */
        std::vector<Entity::Transfer::Transfer> ListServers(const std::string &region = {});

        /**
         * @brief Returns a list of transfer users.
         *
         * @param region AWS region name
         * @param serverId AWS server ID
         * @return list of transfer users
         */
        std::vector<Entity::Transfer::User> ListUsers(const std::string &region, const std::string &serverId);

        /**
         * @brief Returns the total number of servers.
         *
         * @param region AWS region name
         * @return total number of transfer server
         */
        long CountServers(const std::string &region = {});

        /**
         * @brief Deletes an existing transfer manager
         *
         * @param serverId transfer serverID
         * @throws DatabaseException
         */
        void DeleteTransfer(const std::string &serverId);

        /**
         * @brief Deletes all existing transfer server
         *
         * @throws DatabaseException
         */
        void DeleteAllTransfers();

      private:

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Server collection name
         */
        std::string _serverCollectionName;

        /**
         * Transfer in-memory database
         */
        TransferMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_TRANSFER_DATABASE_H
