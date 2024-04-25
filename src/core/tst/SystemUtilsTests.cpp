//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_SYSTEM_UTILS_TEST_H
#define AWSMOCK_CORE_SYSTEM_UTILS_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/SystemUtils.h>

namespace AwsMock::Core {

    class SystemUtilsTest : public ::testing::Test {};

    TEST_F(SystemUtilsTest, GetNodeNameTest) {

        // arrange

        // act
        std::string nodeName = SystemUtils::GetNodeName();

        // assert
        EXPECT_FALSE(nodeName.empty());
    }

    TEST_F(SystemUtilsTest, GetHostNameTest) {

        // arrange

        // act
        std::string hostName = SystemUtils::GetHostName();

        // assert
        EXPECT_FALSE(hostName.empty());
    }

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_SYSTEM_UTILS_TEST_H
