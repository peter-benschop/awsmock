//
// Created by vogje01 on 12/18/23.
//

#ifndef AWMOCK_DTO_SQS_MESSAGE_ATTRBUTE_TEST_H
#define AWMOCK_DTO_SQS_MESSAGE_ATTRBUTE_TEST_H

// GTest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/dto/sqs/MessageAttribute.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define MD5_RESULT "421789f11a0f5cc6f29276b0f69eddb6"

namespace AwsMock::Dto::SQS {

  class MessageAttributeTest : public ::testing::Test {
    protected:

      void SetUp() override {
      }

      void TearDown() override {
      }
  };

  TEST_F(MessageAttributeTest, AttributeMd5Test) {

    // arrange
    Dto::SQS::MessageAttributeList messageAttributes;
    messageAttributes["attribute1"] = {.stringValue="value1", .type=Dto::SQS::MessageAttributeDataType::STRING, .systemAttribute=false};
    messageAttributes["attribute2"] = {.stringValue="value2", .type=Dto::SQS::MessageAttributeDataType::STRING, .systemAttribute=false};

    // act
    std::string result = MessageAttribute::GetMd5UserAttributes(messageAttributes);

    // assert
    EXPECT_FALSE(result.empty());
    EXPECT_STREQ(result.c_str(), MD5_RESULT);
  }
}

#endif // AWMOCK_DTO_SQS_MESSAGE_ATTRBUTE_TEST_H
