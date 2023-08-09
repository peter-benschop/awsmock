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

    TEST_F(AwsUtilsTest, ArnToUrlTest) {

        // arrange
        std::string queueName = "file-delivery1-queue";
        std::string sqsQueueUrl = "http://" + _endpoint + "/" + _accountId + "/" + queueName;
        std::string sqsQueueArn = "arn:aws:sqs:" + _region + ":" + _accountId + ":" + queueName;

        // act
        std::string result = AwsUtils::ConvertSQSQueueArnToUrl(sqsQueueArn, _endpoint);

        // assert
        EXPECT_EQ(result, sqsQueueUrl);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H