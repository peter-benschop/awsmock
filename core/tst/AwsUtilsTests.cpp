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

namespace AwsMock::Core {

    class AwsUtilsTest : public ::testing::Test {

    protected:

        void SetUp() override {
        }

        void TearDown() override {
        }

        std::string _region = "eu-central-1";
        std::string _accountId = "000000000000";
        std::string _endpoint = "localhost:4567";
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
        std::string result = AwsUtils::CreateSQSQueueArn(_region, _accountId, queueName);

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
        std::string result = AwsUtils::ConvertSQSQueueArnToUrl(sqsQueueArn, _endpoint);

        // assert
        EXPECT_STREQ(result.c_str(), sqsQueueUrl.c_str());
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H