//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_MODULE_SERVICE_TEST_H
#define AWMOCK_SERVICE_MODULE_SERVICE_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/ModuleService.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define USER_NAME "test-user"
#define USER_POOL_NAME "test-user-pool"

namespace AwsMock::Service {

  class ModuleServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
        // General configuration
        _region = _configuration.getString("awsmock.region", "eu-central-1");
      }

      void TearDown() override {
      }

      std::string _region;
      Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration(false);
      Core::MetricService _metricService = Core::MetricService(_configuration);
      Database::ModuleDatabase _database = Database::ModuleDatabase(_configuration);

      Service::ServerMap serverMap = {{"s3", new S3Server(_configuration, _metricService)}};
      ModuleService _service = ModuleService(_configuration, serverMap);
  };

  TEST_F(ModuleServiceTest, ModuleListTest) {

    // arrange

    // act
    Database::Entity::Module::ModuleList listResponse = _service.ListModules();

    // assert
    EXPECT_FALSE(listResponse.empty());
  }

  TEST_F(ModuleServiceTest, ModuleStopTest) {

    // arrange

    // act
    Database::Entity::Module::Module stopResponse = _service.StopService("sqs");

    // assert
    EXPECT_TRUE(stopResponse.state == Database::Entity::Module::ModuleState::STOPPED);
  }

  TEST_F(ModuleServiceTest, ModuleStartTest) {

    // arrange
    Database::Entity::Module::Module stopResponse = _service.StopService("sqs");

    // act
    Database::Entity::Module::Module startResponse = _service.StartService("sqs");

    // assert
    EXPECT_TRUE(startResponse.state == Database::Entity::Module::ModuleState::RUNNING);
  }

} // namespace AwsMock::Service

#endif // AWMOCK_SERVICE_MODULE_SERVICE_TEST_H