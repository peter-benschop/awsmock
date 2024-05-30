//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_LAMBDASERVICETEST_H
#define AWMOCK_SERVICE_LAMBDASERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/service/lambda/LambdaService.h"
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/LambdaDatabase.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define RUNTIME "java11"
#define FUNCTION_NAME "test-function"
#define ROLE "lambda-role"
#define HANDLER "de.jensvogt.test-lambda.handler"
#define QUALIFIER "latest"

namespace AwsMock::Service {

    class LambdaServiceTest : public ::testing::Test {

      protected:

        void SetUp() override {
        }

        void TearDown() override {
            _database.DeleteAllLambdas();
        }

        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::LambdaDatabase &_database = Database::LambdaDatabase::instance();
        LambdaService _service;
        std::string testFile;
    };

    TEST_F(LambdaServiceTest, LambdaCreateTest) {

        // arrange
        Dto::Lambda::CreateFunctionRequest request = {{.region = REGION}, FUNCTION_NAME, RUNTIME, ROLE, HANDLER};

        // act
        Dto::Lambda::CreateFunctionResponse response = _service.CreateFunction(request);
        long functionCount = _database.LambdaCount();

        // assert
        EXPECT_TRUE(response.handler == HANDLER);
        EXPECT_TRUE(response.runtime == RUNTIME);
        EXPECT_EQ(1, functionCount);
    }

    TEST_F(LambdaServiceTest, LambdaListTest) {

        // arrange
        Dto::Lambda::CreateFunctionRequest createRequest = {{.region = REGION}, FUNCTION_NAME, RUNTIME, ROLE, HANDLER};
        Dto::Lambda::CreateFunctionResponse createResponse = _service.CreateFunction(createRequest);

        // act
        Dto::Lambda::ListFunctionResponse response = _service.ListFunctions(REGION);

        // assert
        EXPECT_FALSE(response.lambdaList.empty());
        EXPECT_TRUE(response.lambdaList.front().function == FUNCTION_NAME);
    }

    TEST_F(LambdaServiceTest, LambdaCreateTagsTest) {

        // arrange
        Dto::Lambda::CreateFunctionRequest createRequest = {{.region = REGION}, FUNCTION_NAME, RUNTIME, ROLE, HANDLER};
        Dto::Lambda::CreateFunctionResponse createResponse = _service.CreateFunction(createRequest);
        std::string functionArn = createResponse.functionArn;

        // act
        std::map<std::string, std::string> tags;
        tags["test-key1"] = "test-value1";
        tags["test-key2"] = "test-value2";
        Dto::Lambda::CreateTagRequest createTagRequest = {.arn = functionArn, .tags = tags};
        _service.CreateTag(createTagRequest);
        Database::Entity::Lambda::Lambda lambda = _database.GetLambdaByArn(functionArn);

        // assert
        EXPECT_FALSE(lambda.tags.empty());
        EXPECT_TRUE(lambda.tags["test-key1"] == "test-value1");
        EXPECT_TRUE(lambda.tags["test-key2"] == "test-value2");
    }

    TEST_F(LambdaServiceTest, LambdaDeleteTagsTest) {

        // arrange
        Dto::Lambda::CreateFunctionRequest createRequest = {{.region = REGION}, FUNCTION_NAME, RUNTIME, ROLE, HANDLER};
        Dto::Lambda::CreateFunctionResponse createResponse = _service.CreateFunction(createRequest);
        std::string functionArn = createResponse.functionArn;
        std::map<std::string, std::string> tags;
        tags["test-key1"] = "test-value1";
        tags["test-key2"] = "test-value2";
        Dto::Lambda::CreateTagRequest createTagRequest = {.arn = functionArn, .tags = tags};
        _service.CreateTag(createTagRequest);

        // act
        std::vector<std::string> tagKeys = {"test-key1", "test-key2"};
        Dto::Lambda::DeleteTagsRequest deleteTabsRequest(functionArn, tagKeys);
        _service.DeleteTags(deleteTabsRequest);
        Database::Entity::Lambda::Lambda lambda = _database.GetLambdaByArn(functionArn);

        // assert
        EXPECT_TRUE(lambda.tags.empty());
    }

    TEST_F(LambdaServiceTest, LambdaDeleteTest) {

        // arrange
        Dto::Lambda::CreateFunctionRequest createRequest = {{.region = REGION}, FUNCTION_NAME, RUNTIME, ROLE, HANDLER};
        Dto::Lambda::CreateFunctionResponse createResponse = _service.CreateFunction(createRequest);

        // act
        Dto::Lambda::DeleteFunctionRequest deleteRequest = {.functionName = FUNCTION_NAME, .qualifier = QUALIFIER};
        _service.DeleteFunction(deleteRequest);
        long functionCount = _database.LambdaCount();

        // assert
        EXPECT_EQ(0, functionCount);
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_LAMBDASERVICETEST_H