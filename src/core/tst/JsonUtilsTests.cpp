//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_JSON_UTILS_TEST_H
#define AWMOCK_CORE_JSON_UTILS_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// Local includes
#include <awsmock/core/JsonUtils.h>

#define TEST_JSON "{\"testBool\":false, \"testString\":\"testValue\", \"testLong\":10000, \"testInt\":10, \"testFloat\":100.0, \"testDouble\":1000.0, \"testDate\":\"2023-05-25T21:52:17.000000000+00:00\"}"

namespace AwsMock::Core {

    class JsonUtilsTest : public ::testing::Test {};

    TEST_F(JsonUtilsTest, BoolTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        bool result;
        JsonUtils::GetJsonValueBool("testBool", rootObject, result);

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(JsonUtilsTest, StringTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        std::string result;
        JsonUtils::GetJsonValueString("testString", rootObject, result);

        // assert
        EXPECT_STREQ(result.c_str(), "testValue");
    }

    TEST_F(JsonUtilsTest, LongTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        long result;
        JsonUtils::GetJsonValueLong("testLong", rootObject, result);

        // assert
        EXPECT_EQ(result, 10000);
    }

    TEST_F(JsonUtilsTest, IntTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        int result;
        JsonUtils::GetJsonValueInt("testInt", rootObject, result);

        // assert
        EXPECT_EQ(result, 10);
    }

    TEST_F(JsonUtilsTest, FloatTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        float result;
        JsonUtils::GetJsonValueFloat("testFloat", rootObject, result);

        // assert
        EXPECT_EQ(result, 100.0);
    }

    TEST_F(JsonUtilsTest, DoubleTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        double result;
        JsonUtils::GetJsonValueDouble("testDouble", rootObject, result);

        // assert
        EXPECT_EQ(result, 1000.0);
    }

    TEST_F(JsonUtilsTest, DateTest) {

        // arrange
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(TEST_JSON);
        const auto &rootObject = parsed.extract<Poco::JSON::Object::Ptr>();

        // act
        Poco::DateTime result;
        JsonUtils::GetJsonValueDate("testDate", rootObject, result);

        // assert
        EXPECT_EQ(result.year(), 2023);
        EXPECT_EQ(result.month(), 5);
        EXPECT_EQ(result.day(), 25);
    }

}// namespace AwsMock::Core

#endif// AWMOCK_CORE_JSON_UTILS_TEST_H