#ifndef LIBRI_COM_STRINGUTILSTEST_H
#define LIBRI_COM_STRINGUTILSTEST_H

// GTest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poco includes
#include "Poco/Path.h"
#include "Poco/File.h"

// Local includes
#include "../include/libricom/FileUtils.h"
#include "../include/libricom/StreamFilter.h"

namespace Libri::COM
{
    class StringUtilsTest : public ::testing::Test
    {

    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    TEST_F(StringUtilsTest, IsNumericTest)
    {
        // arrange
        std::string value1 = "123456";
        std::string value2 = "abcdef";

        // act
        bool result1 = StringUtils::isNumeric(value1);
        bool result2 = StringUtils::isNumeric(value2);

        // assert
        EXPECT_TRUE(result1);
        EXPECT_FALSE(result2);
    }

    TEST_F(StringUtilsTest, SplitTest)
    {
        // arrange
        std::string value1 = "123 456 789";
        std::string value2 = "123\n456\n789";

        // act
        std::vector<std::string> result1 = StringUtils::split(value1, ' ');
        std::vector<std::string> result2 = StringUtils::split(value2, '\n');

        // assert
        EXPECT_EQ(result1.size(), 3);
        EXPECT_EQ(result2.size(), 3);
    }

    TEST_F(StringUtilsTest, IsUUidTest)
    {
        // arrange
        std::string value1 = "88c3b756-ebc3-46fd-998e-7a2bfb02f347";
        std::string value2 = "88C3B756-EBC3-46FD-998E-7A2BFB02F347";
        std::string value3 = "abscdef";

        // act
        bool result1 = StringUtils::isUuid(value1);
        bool result2 = StringUtils::isUuid(value2);
        bool result3 = StringUtils::isUuid(value3);

        // assert
        EXPECT_TRUE(result1);
        EXPECT_TRUE(result2);
        EXPECT_FALSE(result3);
    }

    TEST_F(StringUtilsTest, StripWhiteSpacesTest)
    {
        // arrange
        std::string value = "   \r\n\r\n\n   ";

        // act
        std::string result = StringUtils::stripWhiteSpaces(value);

        // assert
        EXPECT_EQ(result.length(), 0);
    }

    TEST_F(StringUtilsTest, StripNonWhiteSpacesTest)
    {
        // arrange
        std::string value = "   \r\n\r\n\n   aksjdh";

        // act
        std::string result = StringUtils::stripWhiteSpaces(value);

        // assert
        EXPECT_EQ(result.length(), 17);
        EXPECT_STREQ(result.c_str(), value.c_str());
    }

    TEST_F(StringUtilsTest, EqualTest)
    {
        // arrange
        std::string s1 = "The quick brown fox jumps over the lazy dog";
        std::string s2 = "The quick brown fox jumps over the lazy dog";
        std::string s3 = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";

        // act
        bool result1 = StringUtils::equals(s1, s2);
        bool result2 = StringUtils::equalsIgnoreCase(s1, s3);

        // assert
        EXPECT_TRUE(result1);
        EXPECT_TRUE(result2);
    }

    TEST_F(StringUtilsTest, ContainsTest)
    {
        // arrange
        std::string s1 = "The quick brown fox jumps over the lazy dog";
        std::string s2 = "quick brown fox";

        // act
        bool result = StringUtils::contains(s1, s2);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(StringUtilsTest, StripTest)
    {
        // arrange
        std::string s1 = "Threads:        80";
        std::string s2 = "   80    ";

        // act
        std::string result1 = StringUtils::split(s1, ':')[1];
        std::string result2 = StringUtils::trim(StringUtils::split(s1, ':')[1]);
        std::string result3 = StringUtils::trim(s2);

        // assert
        EXPECT_STREQ(result1.c_str(), "        80");
        EXPECT_STREQ(result2.c_str(), "80");
        EXPECT_STREQ(result3.c_str(), "80");
    }

    TEST_F(StringUtilsTest, StringDoubleTest)
    {
        // arrange
        std::string s1 = " 80 ";

        // act
        double result1 = std::stod(StringUtils::trim(s1));

        // assert
        EXPECT_EQ(80.0, result1);
    }

    TEST_F(StringUtilsTest, UrlEncodeTest)
    {
        // arrange
        std::string input = "/abc/xyz/\n ";

        // act
        std::string result = StringUtils::UrlEncode(input);

        // assert
        EXPECT_STREQ("/abc/xyz/%0A%20", result.c_str());
    }

    TEST_F(StringUtilsTest, UrlEncodeSpecialCharactersTest)
    {
        // arrange
        std::string input = "/abc/xyz/\n +";

        // act
        std::string result = StringUtils::UrlEncode(input);

        // assert
        EXPECT_STREQ("/abc/xyz/%0A%20%2B", result.c_str());
    }

    TEST_F(StringUtilsTest, StripLineEndingsTest)
    {
        // arrange
        std::string input = "/abc/xyz/\r\n";

        // act
        std::string result = StringUtils::StripLineEndings(input);

        // assert
        EXPECT_STREQ("/abc/xyz/", result.c_str());
    }
} // namespace Libri::COM
#endif // LIBRI_COM_STRINGUTILSTEST_H
