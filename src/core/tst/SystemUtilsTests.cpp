//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_SYSTEMUTILSTEST_H
#define AWSMOCK_CORE_SYSTEMUTILSTEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/SystemUtils.h>

namespace AwsMock::Core {

  class SystemUtilsTest : public ::testing::Test {

  protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
  };

  TEST_F(SystemUtilsTest, GetNodeNameTest) {

    // arrange

    // act
    std::string nodeName = SystemUtils::GetNodeName();

    // assert
    EXPECT_TRUE(nodeName.length() > 0);
  }

  TEST_F(SystemUtilsTest, GetHostNameTest) {

    // arrange

    // act
    std::string hostName = SystemUtils::GetHostName();

    // assert
    EXPECT_TRUE(hostName.length() > 0);
  }

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_SYSTEMUTILSTEST_H
