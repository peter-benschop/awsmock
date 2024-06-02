//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_CONFIGURATION_TEST_H
#define AWSMOCK_CORE_CONFIGURATION_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/TestUtils.h>

namespace AwsMock::Core {

    class ConfigurationTest : public ::testing::Test {

      protected:

        void SetUp() override {
        }

        void TearDown() override {
        }

        Configuration _configuration = Configuration(TMP_PROPERTIES_FILE);
    };

    TEST_F(ConfigurationTest, EmptyFilenameTest) {

        // arrange

        // act
        EXPECT_THROW({
            try {
                Configuration configuration = Configuration("");
            } catch (const CoreException &e) {
                EXPECT_STREQ("Empty filename", e.message().c_str());
                EXPECT_STREQ("CoreException: ", e.name());
                throw;
            } }, CoreException);

        // assert
    }

    TEST_F(ConfigurationTest, ConstructorTest) {

        // arrange
        Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        EXPECT_STREQ(configuration->GetFilename().c_str(), TMP_PROPERTIES_FILE);
        EXPECT_FALSE(configuration->getString("awsmock.log.level").empty());
    }

    TEST_F(ConfigurationTest, SetValueTest) {

        // arrange
        Configuration *configuration = nullptr;
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // act
        if (configuration != nullptr) {
            configuration->SetValue("awsmock.log.level", std::string("error"));
        }

        // assert
        EXPECT_STREQ(configuration->getString("awsmock.log.level").c_str(), "error");
    }

    TEST_F(ConfigurationTest, EnvironmentTest) {

        // arrange
#ifdef WIN32
        _putenv_s("AWSMOCK_LOG_LEVEL", "error");
#else
        setenv("AWSMOCK_LOG_LEVEL", "error", true);
#endif
        Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        std::string tmp = configuration->getString("awsmock.log.level");
        EXPECT_STREQ(configuration->getString("awsmock.log.level").c_str(), "error");
    }

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_CONFIGURATION_TEST_H