//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_AWSUTILSTEST_H
#define AWMOCK_CORE_AWSUTILSTEST_H

// GTest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poco includes
#include "Poco/Path.h"

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/TestUtils.h>

namespace AwsMock::Core {

  class AwsUtilsTest : public ::testing::Test {

  public:
    void SetUp() override {
      _region = _configuration.getString("awsmock.region");
      _accountId = _configuration.getString("awsmock.account.id");
      _endpoint = SystemUtils::GetHostName() + ":" + _configuration.getString("awsmock.gateway.port");
    }

  protected:
    std::string _region, _accountId, _endpoint;
    Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
  };

  TEST_F(AwsUtilsTest, CreateS3ArnTest) {

    // arrange
    std::string bucket = "testBucket";
    std::string key = "testKey";
    std::string s3Arn = "arn:aws:s3:" + _region + ":" + _accountId + ":" + bucket + "/" + key;

    // act
    std::string result = AwsUtils::CreateS3Arn(_region, _accountId, bucket, key);

    // assert
    EXPECT_STREQ(result.c_str(), s3Arn.c_str());
  }

  TEST_F(AwsUtilsTest, CreateSqsArnTest) {

    // arrange
    std::string queueName = "testQueue";
    std::string sqsQueueArn = "arn:aws:sqs:" + _region + ":" + _accountId + ":" + queueName;

    // act
    std::string result = AwsUtils::CreateSqsQueueArn(_configuration, queueName);

    // assert
    EXPECT_STREQ(result.c_str(), sqsQueueArn.c_str());
  }

  TEST_F(AwsUtilsTest, CreateSNSTopicTest) {

    // arrange
    std::string topicName = "testTopic";
    std::string snsTopic3Arn = "arn:aws:sns:" + _region + ":" + _accountId + ":" + topicName;

    // act
    std::string result = AwsUtils::CreateSNSTopicArn(_region, _accountId, topicName);

    // assert
    EXPECT_STREQ(result.c_str(), snsTopic3Arn.c_str());
  }

  TEST_F(AwsUtilsTest, ConvertArnToUrlTest) {

    // arrange
    std::string queueName = "file-delivery1-queue";
    std::string sqsQueueUrl = "http://" + _endpoint + "/" + _accountId + "/" + queueName;
    std::string sqsQueueArn = "arn:aws:sqs:" + _region + ":" + _accountId + ":" + queueName;

    // act
    std::string result = AwsUtils::ConvertSQSQueueArnToUrl(_configuration, sqsQueueArn);

    // assert
    EXPECT_STREQ(result.c_str(), sqsQueueUrl.c_str());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H