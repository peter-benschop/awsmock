//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_TRANSFERDATABASE_H
#define AWSMOCK_DB_TRANSFERDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/transfer/Transfer.h>

namespace AwsMock::Database {

    class TransferDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit TransferDatabase(const Core::Configuration &configuration);

      /**
       * Check existence of lambda
       *
       * @param region AWS region name
       * @param transferName AWS transfer name
       * @return true if transfer server already exists
       * @throws DatabaseException
       */
      bool TransferExists(const std::string &region, const std::string &transferName);

      /**
       * Check existence of lambda
       *
       * @param transferName AWS transfer name
       * @return true if transfer server already exists
       * @throws DatabaseException
       */
      bool TransferExists(const Entity::Transfer::Transfer &transferName);

      /**
       * Check existence of lambda
       *
       * @param transferName AWS transfer name
       * @return true if transfer server already exists
       * @throws DatabaseException
       */
      bool TransferExists(const std::string &transferName);

      /**
       * Create a new lambda function
       *
       * @param lambda lambda entity
       * @return created lambda entity.
       */
      Entity::Transfer::Transfer CreateTransfer(const Entity::Transfer::Transfer &lambda);


      /**
       * Updates an existing transfer server
       *
       * @param lambda lambda entity
       * @return updated lambda entity.
       */
      Entity::Transfer::Transfer UpdateTransfer(const Entity::Transfer::Transfer &lambda);


      /**
       * Created or updates an existing transfer server
       *
       * @param lambda lambda entity
       * @return created or updated lambda entity.
       */
      Entity::Transfer::Transfer CreateOrUpdateTransfer(const Entity::Transfer::Transfer &lambda);

      /**
       * Returns a transfer server entity by primary key
       *
       * @param oid transfer server primary key
       * @return transfer server entity
       * @throws DatabaseException
       */
      Entity::Transfer::Transfer GetTransferById(bsoncxx::oid oid);

      /**
       * Returns a transfer server entity by primary key
       *
       * @param oid transfer server primary key
       * @return transfer server entity
       * @throws DatabaseException
       */
      Entity::Transfer::Transfer GetTransferById(const std::string &oid);

      /**
       * Returns a transfer server entity by server ID
       *
       * @param serverId transfer server ID
       * @return transfer server entity
       * @throws DatabaseException
       */
      Entity::Transfer::Transfer GetTransferByServerId(const std::string &serverId);

      /**
       * Returns a transfer server entity by ARN
       *
       * @param arn transfer server ARN
       * @return transfer server entity
       * @throws DatabaseException
       */
      Entity::Transfer::Transfer GetTransferByArn(const std::string &arn);

      /**
       * Returns a list of transfer server.
       *
       * @param region AWS region name
       * @return list of transfer server
       */
      std::vector<Entity::Transfer::Transfer> ListTransfers(const std::string &region);

      /**
       * Deletes an existing transfer server
       *
       * @param transferName transfer server name
       * @throws DatabaseException
       */
      void DeleteTransfer(const std::string &transferName);

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
       * Transfer collection
       */
      mongocxx::collection _transferCollection{};

    };

} // namespace AwsMock::Database

#endif // AWSMOCK_DB_TRANSFERDATABASE_H
