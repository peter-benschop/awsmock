//
// Created by vogje01 on 01/09/2022.
//

// C++ standard includes
#include <string>

// GTest includes
#include "gtest/gtest.h"

// AwsMock includes
#include <awsmock/core/TestUtils.h>

class TestEnvironment final : public ::testing::Environment {
  public:

    // Initialise a test configuration.
    void SetUp() override {
        AwsMock::Core::TestUtils::CreateTestConfigurationFile();
    }
};

int main(int argc, char **argv) {
    // Run data
    testing::InitGoogleTest(&argc, argv);
    AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}
