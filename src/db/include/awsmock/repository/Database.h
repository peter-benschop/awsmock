//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_DATABASE_H
#define AWSMOCK_REPOSITORY_DATABASE_H

// C++ standard includes
#include <string>

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>

// Poco includes
#include <Poco/Util/AbstractConfiguration.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>

namespace AwsMock::Database {

  class Database {

  public:

    /**
     * Constructor
     *
     * @param configuration configuration properties
     */
    explicit Database(Core::Configuration &configuration);

    /**
     * Initialize mongodb
     */
    void Initialize();

    /**
     * Returns a MongoDB connection from the pool
     *
     * @return MongoDB database client
     */
    mongocxx::database GetConnection();

    /**
     * Check all indexes.
     *
     * <p>Normally done during manager StartServer.</p>
     */
    void CreateIndexes();

    /**
     * Returns a client session
     *
     * @return client session
     */
    mongocxx::client_session GetSession();

    /**
     * Check whether we are running without database
     */
    bool HasDatabase() const;

    /**
     * Start the database
     */
    void StartDatabase();

    /**
     * Stops the database
     */
    void StopDatabase();

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Application configuration
     */
    Core::Configuration &_configuration;

    /**
     * Database name
     */
    std::string _name;

    /**
     * Database host
     */
    std::string _host;

    /**
     * Database port
     */
    int _port;

    /**
     * Database user
     */
    std::string _user;

    /**
     * Database password
     */
    std::string _password;

    /**
     * MongoDB URI
     */
    mongocxx::uri _uri;

    /**
     * Database client
     */
    mongocxx::client _client;

    /**
     * Database flag
     */
    bool _useDatabase;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_DATABASE_H
