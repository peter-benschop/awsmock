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

#define MD5_RESULT "c48838208d2b4e14e3ca0093a8443f09"

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
    messageAttributes["my_attribute_name_1"] = {.stringValue="my_attribute_value_1", .type=Dto::SQS::MessageAttributeDataType::STRING, .systemAttribute=false};
    messageAttributes["my_attribute_name_2"] = {.stringValue="my_attribute_value_2", .type=Dto::SQS::MessageAttributeDataType::STRING, .systemAttribute=false};

    // act
    std::string result = MessageAttribute::GetMd5Attributes(messageAttributes, false);

    // assert
    EXPECT_FALSE(result.empty());
    EXPECT_STREQ(result.c_str(), MD5_RESULT);
  }
}

#endif // AWMOCK_DTO_SQS_MESSAGE_ATTRBUTE_TEST_H
