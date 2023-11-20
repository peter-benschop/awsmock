//
// Created by vogje01 on 01/09/2022.
//

// GTest includes
#include "gtest/gtest.h"

// MongoDB includes
#include <mongocxx/instance.hpp>

// AwsMock includes
#include <awsmock/core/TestUtils.h>

class TestEnvironment : public ::testing::Environment {
public:

  // Initialise a test configuration.
  void SetUp() override {
    AwsMock::Core::TestUtils::CreateTestConfigurationFile();
  }
};

int main(int argc, char **argv) {

  // Initialize MongoDB
  mongocxx::instance _instance{};

  // Run tests
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);
  int ret = RUN_ALL_TESTS();

  return ret;
}