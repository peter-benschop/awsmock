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
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/transfer/Transfer.h>
#include <awsmock/entity/transfer/User.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class TransferMemoryDb {

  public:

    /**
     * Constructor
     */
    TransferMemoryDb();

    /**
     * Singleton instance
     */
    static TransferMemoryDb &instance() {
      static Poco::SingletonHolder<TransferMemoryDb> sh;
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
     * Returns a list of transfer manager.
     *
     * @param region AWS region name
     * @return list of transfer manager
     */
    std::vector<Entity::Transfer::Transfer> ListServers(const std::string &region);

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

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

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_TRANSFERMEMORYDB_H
