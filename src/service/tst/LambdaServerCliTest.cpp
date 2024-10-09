//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H
#define AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/lambda/LambdaServer.h>
#include <awsmock/service/lambda/LambdaService.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
#define FUNCTION_NAME std::string("test-function")
#define FUNCTION_FILE std::string("/tmp/java-basic-1.0-SNAPSHOT.jar")
#define ROLE std::string("arn:aws:iam::000000000000:role/lambda-role")
#define CODE std::string("S3Bucket=lambdaBucket,S3Key=lambdaKey")
#define RUNTIME std::string("java11")

namespace AwsMock::Service {

    /**
   * AwsMock lambda integration test.
   *
   * <p>In order to run the test the AWS test lambdas should be installed in /usr/local/lib. See https://github.com/awsdocs/aws-lambda-developer-guide/tree/main/sample-apps/java-basic for details.</p>
   */
    class LambdaServerCliTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // Check lambda examples
            if (!Core::FileUtils::FileExists(FUNCTION_FILE)) {
                SUCCEED();
                return;
            }

            // Define endpoint
            std::string _port = _configuration.getString("awsmock.service.lambda.port", std::to_string(GATEWAY_DEFAULT_PORT));
            std::string _host = _configuration.getString("awsmock.service.lambda.host", GATEWAY_DEFAULT_HOST);
            _configuration.setString("awsmock.service.gateway.http.port", _port);
            _accountId = _configuration.getString("awsmock.account.id", ACCOUNT_ID);
            _endpoint = "http://" + _host + ":" + _port;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
            //            _gatewayServer->Initialize();
            //_gatewayServer->Start();
        }

        void TearDown() override {
            try {
                Dto::Lambda::DeleteFunctionRequest deleteFunctionRequest = {.functionName = FUNCTION_NAME, .qualifier = "latest"};
                _lambdaService.DeleteFunction({.functionName = FUNCTION_NAME, .qualifier = "latest"});
            } catch (Core::ServiceException &ex) {
                // Do nothing
            }
            // _gatewayServer->Stop();
        }

        std::string _endpoint, _accountId;
        boost::asio::io_service _ios{10};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::LambdaDatabase &_database = Database::LambdaDatabase::instance();
        Service::LambdaService _lambdaService;
        Service::S3Service _s3Service;
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    /*TEST_F(LambdaServerCliTest, LambdaCreateTest) {

        // check lambda examples
        if (!Core::FileUtils::FileExists(FUNCTION_FILE)) {
            std::cerr << "Lambda test function missing" << std::endl;
            SUCCEED();
            return;
        }

        // arrange
        std::ifstream input_file(FUNCTION_FILE, std::ios::binary);
        Dto::S3::PutObjectRequest request = {.region = REGION, .bucket = "lambdaBucket", .key = "lambdaKey"};
        _s3Service.PutObject(request, input_file, false);

        // act
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws lambda create-function --function-name " + FUNCTION_NAME + " --role " + ROLE + " --code " + CODE + " --runtime " + RUNTIME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::Lambda::LambdaList lambdaList = _database.ListLambdas();

        // assert
        EXPECT_EQ(0, createResult.status);
        EXPECT_EQ(1, lambdaList.size());
    }

    TEST_F(LambdaServerCliTest, LambdaListTest) {

        // check lambda examples
        if (!Core::FileUtils::FileExists(FUNCTION_FILE)) {
            std::cerr << "Lambda test function missing" << std::endl;
            SUCCEED();
            return;
        }

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws lambda create-function --function-name " + FUNCTION_NAME + " --role " + ROLE + " --code " + CODE + " --runtime " + RUNTIME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);

        // act
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws lambda list-functions --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, listResult.status);
        EXPECT_FALSE(listResult.output.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, FUNCTION_NAME));
    }*/

    /*TEST_F(LambdaServerCliTest, BucketDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 rb " + TEST_BUCKET + " --endpoint " + _endpoint);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, bucketList.size());
  }*/

}// namespace AwsMock::Service

#endif// AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H