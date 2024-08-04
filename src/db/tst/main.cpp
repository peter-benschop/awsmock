//
// Created by vogje01 on 01/09/2022.
//

// C++ includes
#include <memory>

// GTest includes
#include "gtest/gtest.h"

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

// AwsMock includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/utils/ConnectionPool.h>

class TestEnvironment : public ::testing::Environment {
  public:

    // Initialise a test configuration.
    void SetUp() override {
        AwsMock::Core::TestUtils::CreateTestConfigurationFile();
        InitializeDatabase();
    }

    /**
     * Initialize database
     */
    static void InitializeDatabase() {

        // Get database variables
        AwsMock::Core::Configuration &_configuration = AwsMock::Core::Configuration::instance();
        std::string name = _configuration.getString("awsmock.mongodb.name", "awsmock");
        std::string host = _configuration.getString("awsmock.mongodb.host", "localhost");
        std::string user = _configuration.getString("awsmock.mongodb.user", "admin");
        std::string password = _configuration.getString("awsmock.mongodb.password", "admin");
        int _port = _configuration.getInt("awsmock.mongodb.port", 27017);
        int poolSize = _configuration.getInt("awsmock.mongodb.pool.size", 256);

        // MongoDB URL
        mongocxx::uri _uri("mongodb://" + user + ":" + password + "@" + host + ":" + std::to_string(_port) + "/?maxPoolSize=" + std::to_string(poolSize));

        auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
        AwsMock::Database::ConnectionPool &pool = AwsMock::Database::ConnectionPool::instance();

        // Options
        mongocxx::options::client client_options;
        auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
        client_options.server_api_opts(api);
        pool.configure(std::move(instance), bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(_uri), std::move(client_options)));
    }
};

int main(int argc, char **argv) {

    // Initialize MongoDB
    // mongocxx::instance _instance{};

    // Run data
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    int ret = RUN_ALL_TESTS();

    return ret;
}