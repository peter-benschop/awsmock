//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWS_MOCK_CORE_CONFIGURATION_TEST_H
#define AWS_MOCK_CORE_CONFIGURATION_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/core/config/YamlConfiguration.h>

namespace AwsMock::Core {

    class ConfigurationTest : public ::testing::Test {

      protected:

        void SetUp() override {
        }

        void TearDown() override {
        }

        YamlConfiguration _configuration = YamlConfiguration(TMP_PROPERTIES_FILE);
    };

    TEST_F(ConfigurationTest, EmptyFilenameTest) {

        // arrange

        // act
        EXPECT_THROW({
            try {
                auto configuration = YamlConfiguration("");
            } catch (const CoreException &e) {
                EXPECT_STREQ("Empty filename", e.message().c_str());
                throw;
            } }, CoreException);

        // assert
    }

    TEST_F(ConfigurationTest, ConstructorTest) {

        // arrange
        const YamlConfiguration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new YamlConfiguration(TMP_PROPERTIES_FILE); });

        // assert
        EXPECT_STREQ(configuration->GetFilename().c_str(), TMP_PROPERTIES_FILE);
        EXPECT_FALSE(configuration->GetValueString("awsmock.logging.level").empty());
    }

    TEST_F(ConfigurationTest, SetValueTest) {

        // arrange
        YamlConfiguration *configuration = nullptr;
        EXPECT_NO_THROW({ configuration = new YamlConfiguration(TMP_PROPERTIES_FILE); });

        // act
        if (configuration != nullptr) {
            configuration->SetValue("awsmock.logging.level", std::string("error"));
        }

        // assert
        EXPECT_STREQ(configuration->GetValueString("awsmock.logging.level").c_str(), "error");
    }

    TEST_F(ConfigurationTest, EnvironmentTest) {

        // arrange
        setenv("AWSMOCK_LOG_LEVEL", "error", true);
        const YamlConfiguration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new YamlConfiguration(TMP_PROPERTIES_FILE); });

        // assert
        if (configuration != nullptr) {
            std::string tmp = configuration->GetValueString("service.logging.level");
            EXPECT_STREQ(configuration->GetValueString("awsmock.logging.level").c_str(), "error");
        } else {
            FAIL();
        }
    }

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_CONFIGURATION_TEST_H