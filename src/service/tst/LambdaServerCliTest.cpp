//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H
#define AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>
#include "awsmock/service/lambda/LambdaServer.h"
#include "awsmock/service/lambda/LambdaService.h"

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
#define FUNCTION_NAME std::string("test-function")
#define ROLE std::string("arn:aws:iam::000000000000:role/lambda-role")
#define CODE  std::string("S3Bucket=lambdaBucket,S3Key=lambdaKey")
#define RUNTIME  std::string("java17")

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
      if(!Core::FileUtils::FileExists("/usr/local/lib/aws-lambda-example.jar")) {
        SUCCEED();
        return;
      }

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.lambda.port", std::to_string(LAMBDA_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.lambda.host", LAMBDA_DEFAULT_HOST);
      _configuration.setString("awsmock.service.gateway.port", _port);
      _accountId = _configuration.getString("awsmock.account.userPoolId", ACCOUNT_ID);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      _lambdaServer.Start();
    }

    void TearDown() override {
      _database.DeleteAllLambdas();
      _lambdaServer.StopServer();
    }

    std::string _endpoint, _accountId;
    Core::Configuration& _configuration = Core::Configuration().instance();
    Core::MetricService& _metricService = Core::MetricService::instance();
    Database::LambdaDatabase& _database = Database::LambdaDatabase::instance();
    LambdaServer _lambdaServer = LambdaServer(_configuration, _metricService);
  };

  TEST_F(LambdaServerCliTest, LambdaCreateTest) {

    // check lambda examples
    if(!Core::FileUtils::FileExists("/usr/local/lib/aws-lambda-example.jar")) {
      std::cerr << "Lambda test function missing" << std::endl;
      SUCCEED();
      return;
    }

    // arrange

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
    if(!Core::FileUtils::FileExists("/usr/local/lib/aws-lambda-example.jar")) {
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
    EXPECT_TRUE(listResult.output.length() > 0);
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, FUNCTION_NAME));
  }

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

} // namespace AwsMock::Service

#endif // AWMOCK_LAMBDA_LAMBDASERVERCLITEST_H