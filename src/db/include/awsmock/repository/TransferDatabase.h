//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_TRANSFERDATABASE_H
#define AWSMOCK_REPOSITORY_TRANSFERDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/memorydb/TransferMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database {

  class TransferDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit TransferDatabase();

      /**
       * Singleton instance
       */
      static TransferDatabase &instance() {
        static Poco::SingletonHolder<TransferDatabase> sh;
        return *sh.get();
      }

      /**
       * Check existence of lambda
       *
       * @param region AWS region name
       * @param serverId AWS server ID
       * @return true if transfer manager already exists
       * @throws DatabaseException
       */
      bool TransferExists(const std::string &region, const std::string &serverId);

      /**
       * Check existence of lambda
       *
       * @param transfer AWS transfer
       * @return true if transfer manager already exists
       * @throws DatabaseException
       */
      bool TransferExists(const Entity::Transfer::Transfer &transfer);

      /**
       * Check existence of lambda
       *
       * @param transferName AWS transfer name
       * @return true if transfer manager already exists
       * @throws DatabaseException
       */
      bool TransferExists(const std::string &transferName);

      /**
       * Check existence of lambda
       *
       * @param region AWS region name
       * @param protocols list of protocols
       * @return true if transfer manager already exists
       * @throws DatabaseException
       */
      bool TransferExists(const std::string &region, const std::vector<std::string> &protocols);

      /**
       * Create a new lambda function
       *
       * @param lambda lambda entity
       * @return created lambda entity.
       */
      Entity::Transfer::Transfer CreateTransfer(const Entity::Transfer::Transfer &lambda);

      /**
       * Updates an existing transfer manager
       *
       * @param lambda lambda entity
       * @return updated lambda entity.
       */
      Entity::Transfer::Transfer UpdateTransfer(const Entity::Transfer::Transfer &lambda);

      /**
       * Created or updates an existing transfer manager
       *
       * @param lambda lambda entity
       * @return created or updated lambda entity.
       */
      Entity::Transfer::Transfer CreateOrUpdateTransfer(const Entity::Transfer::Transfer &lambda);

      /**
       * Returns a transfer manager entity by primary key
       *
       * @param oid transfer manager primary key
       * @return transfer manager entity
       * @throws DatabaseException
       */
      Entity::Transfer::Transfer GetTransferById(bsoncxx::oid oid);

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
       * Returns a list of transfer manager.
       *
       * @param region AWS region name
       * @return list of transfer manager
       */
      std::vector<Entity::Transfer::Transfer> ListServers(const std::string &region = {});

      /**
       * Deletes an existing transfer manager
       *
       * @param serverId transfer serverID
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
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Use MongoDB
       */
      bool _useDatabase;

      /**
       * Database name
       */
      std::string _databaseName;

      /**
       * Transfer in-memory database
       */
      TransferMemoryDb &_memoryDb;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_TRANSFERDATABASE_H
