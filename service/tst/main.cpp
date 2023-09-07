//
// Created by vogje01 on 01/09/2022.
//

// C++ include
#include <fstream>

// Curl includes
#include <curl/curl.h>

// GTest includes
#include "gtest/gtest.h"

// Test includes
#include <awsmock/core/TestUtils.h>

class TestEnvironment : public ::testing::Environment {
public:

  // Initialise a test configuration.
  void SetUp() override {
      AwsMock::Core::TestUtils::CreateTestConfigurationFile();
  }
};

int main(int argc, char **argv) {

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_ALL);

    // Run tests
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    int ret = RUN_ALL_TESTS();

    return ret;
}