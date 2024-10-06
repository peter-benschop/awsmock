//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_MODULE_SERVICE_TEST_H
#define AWMOCK_SERVICE_MODULE_SERVICE_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include "awsmock/service/module/ModuleService.h"
#include <awsmock/repository/ModuleDatabase.h>

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

            _s3Server = std::make_shared<S3Server>(_pool);
            _sqsServer = std::make_shared<SQSServer>(_pool);

            _serverMap = {
                    {"s3", _s3Server},
                    {"sqs", _sqsServer}};
            _service = std::make_shared<ModuleService>();
        }

        void TearDown() override {
            _s3Server->Stop();
            _sqsServer->Stop();
            _serverMap.clear();
        }

        Service::ServerMap _serverMap;
        boost::asio::thread_pool _pool = (10);
        std::shared_ptr<ModuleService> _service;
        std::shared_ptr<S3Server> _s3Server;
        std::shared_ptr<SQSServer> _sqsServer;
        Database::ModuleDatabase &_database = Database::ModuleDatabase::instance();
    };

    /*TEST_F(ModuleServiceTest, ModuleListTest) {

        // arrange

        // act
        Database::Entity::Module::ModuleList listResponse = _service->ListModules();

        // assert
        EXPECT_FALSE(listResponse.empty());
    }

    TEST_F(ModuleServiceTest, ModuleStopTest) {

        // arrange
        Dto::Common::Services services;
        services.serviceNames.emplace_back("sqs");
        Database::Entity::Module::Module startResponse = _lambdaService->StartModules(services);

        // act
        Database::Entity::Module::Module stopResponse =_lambdaService->StopModules(services);

        // assert
        EXPECT_TRUE(stopResponse.state == Database::Entity::Module::ModuleState::STOPPED);
    }

    TEST_F(ModuleServiceTest, ModuleStartTest){

            // arrange
            Dto::Common::Services services;
            services.serviceNames.emplace_back("sqs");

            // act
            Database::Entity::Module::Module startResponse =_lambdaService->StartModules(services);

            // assert
            //EXPECT_TRUE(startResponse.state == Database::Entity::Module::ModuleState::RUNNING);
    }*/

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_MODULE_SERVICE_TEST_H