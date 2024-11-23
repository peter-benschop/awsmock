//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWS_MOCK_CORE_CONFIGURATION_TEST_H
#define AWS_MOCK_CORE_CONFIGURATION_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/core/config/Configuration.h>

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
                auto configuration = Configuration("");
            } catch (const CoreException &e) {
                EXPECT_STREQ("Empty filename", e.message().c_str());
                throw;
            } }, CoreException);

        // assert
    }

    TEST_F(ConfigurationTest, ConstructorTest) {

        // arrange
        const Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        EXPECT_STREQ(configuration->GetFilename().c_str(), TMP_PROPERTIES_FILE);
        EXPECT_FALSE(configuration->getString("awsmock.service.logging.level").empty());
    }

    TEST_F(ConfigurationTest, SetValueTest) {

        // arrange
        Configuration *configuration = nullptr;
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // act
        if (configuration != nullptr) {
            configuration->SetValue("awsmock.service.logging.level", std::string("error"));
        }

        // assert
        EXPECT_STREQ(configuration->getString("awsmock.service.logging.level").c_str(), "error");
    }

    TEST_F(ConfigurationTest, EnvironmentTest) {

        // arrange
        setenv("AWSMOCK_LOG_LEVEL", "error", true);
        const Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        if (configuration != nullptr) {
            std::string tmp = configuration->getString("awsmock.service.logging.level");
            EXPECT_STREQ(configuration->getString("awsmock.service.logging.level").c_str(), "error");
        } else {
            FAIL();
        }
    }

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_CONFIGURATION_TEST_H