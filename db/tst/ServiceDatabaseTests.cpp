//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SERVICEDATABASETEST_H
#define AWMOCK_CORE_SERVICEDATABASETEST_H

// C++ standard includes
#include <iostream>
#include <vector>

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/ServiceDatabase.h>

// MongoDB includes
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/client.hpp>

#define SERVICE "test-service"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  class ServiceDatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
        _region = _configuration.getString("awsmock.region");
      }

      void TearDown() override {
        _serviceDatabase.DeleteAllServices();
      }

      std::string _region;
      Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
      ServiceDatabase _serviceDatabase = ServiceDatabase(_configuration);
  };

  TEST_F(ServiceDatabaseTest, ServiceCreateTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};

    // act
    Entity::Service::Service result = _serviceDatabase.CreateService(service);

    // assert
    EXPECT_TRUE(result.name == SERVICE);
    EXPECT_TRUE(result.status == Entity::Service::ServiceStatus::RUNNING);
  }

  TEST_F(ServiceDatabaseTest, ServiceExistsTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);

    // act
    bool result1 = _serviceDatabase.ServiceExists(service.name);
    bool result2 = _serviceDatabase.ServiceExists("blabla");

    // assert
    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
  }

  TEST_F(ServiceDatabaseTest, ServiceActiveTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);

    // act
    bool result = _serviceDatabase.IsActive(service.name);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(ServiceDatabaseTest, ServiceGetByNameTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);

    // act
    Entity::Service::Service result = _serviceDatabase.GetServiceByName(service.name);

    // assert
    EXPECT_TRUE(result.name == SERVICE);
  }

  TEST_F(ServiceDatabaseTest, ServiceGetByIdTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);
    bsoncxx::oid oid(service.oid);

    // act
    Entity::Service::Service result = _serviceDatabase.GetServiceById(oid);

    // assert
    EXPECT_TRUE(result.name == SERVICE);
  }

  TEST_F(ServiceDatabaseTest, ServiceUpdateTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);
    service.status = Entity::Service::ServiceStatus::STOPPED;

    // act
    Entity::Service::Service result = _serviceDatabase.UpdateService(service);

    // assert
    EXPECT_TRUE(result.status == Entity::Service::ServiceStatus::STOPPED);
  }

  TEST_F(ServiceDatabaseTest, ServiceDeleteTest) {

    // arrange
    Entity::Service::Service service = {.name=SERVICE, .status=Entity::Service::ServiceStatus::RUNNING};
    service = _serviceDatabase.CreateService(service);

    // act
    _serviceDatabase.DeleteService(service);
    int count = _serviceDatabase.ServiceCount();

    // assert
    EXPECT_EQ(0, count);
  }

} // namespace AwsMock::Database

#endif // AWMOCK_CORE_SERVICEDATABASETEST_H