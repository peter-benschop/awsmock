//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_DATABASETEST_H
#define AWMOCK_CORE_DATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/db/Database.h>

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    class DatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
      }

      Core::Configuration _configuration = Core::Configuration("/tmp/aws-mock.properties");
      Database _database = Database(_configuration);
    };

    TEST_F(DatabaseTest, ConstructorTest) {

        // arrange
        int count = 0;
        Poco::Data::Session session = _database.GetSession();

        // act
        Poco::Data::Statement stmt(session);
        stmt << "SELECT COUNT(*) FROM service", into(count), now;

        // assert
        EXPECT_EQ(count, 0);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H