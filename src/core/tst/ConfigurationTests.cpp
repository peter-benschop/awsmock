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

        //YamlConfiguration _configuration = YamlConfiguration(TMP_PROPERTIES_FILE);
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
        Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        EXPECT_STREQ(configuration->GetFilename().c_str(), TMP_PROPERTIES_FILE);
        EXPECT_FALSE(configuration->GetValueString("awsmock.logging.level").empty());
    }

    TEST_F(ConfigurationTest, SetValueTest) {
        // arrange
        Configuration *configuration = nullptr;
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

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
        Configuration *configuration = nullptr;

        // act
        EXPECT_NO_THROW({ configuration = new Configuration(TMP_PROPERTIES_FILE); });

        // assert
        if (configuration != nullptr) {
            std::string tmp = configuration->GetValueString("service.logging.level");
            EXPECT_STREQ(configuration->GetValueString("awsmock.logging.level").c_str(), "error");
        } else {
            FAIL();
        }
    }

    TEST_F(ConfigurationTest, YamlConfiggurationTest) {
        // arrange
        const std::string yamlString = "awsmock:\n\t"
                                       "region: eu-central-1\n\t"
                                       "user: none\n\t"
                                       "access: \n\t\t"
                                       "key-id: none\n\t\t"
                                       "secret-access-key: none\n\t\t"
                                       "account-id: 000000000000\n\t\t";
        const std::string yamlFile = FileUtils::CreateTempFile("yaml", yamlString);
        auto configuration = Configuration(yamlFile);

        // act
        const std::string region = configuration.GetValueString("awsmock.region");
        const std::string keyId = configuration.GetValueString("awsmock.access.key-id");

        // assert
        EXPECT_TRUE(region == "eu-central-1");
        EXPECT_TRUE(keyId == "none");
    }
}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_CONFIGURATION_TEST_H
