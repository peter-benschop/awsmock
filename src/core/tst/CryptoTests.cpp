//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_CRYPTO_UTILS_TEST_H
#define AWSMOCK_CORE_CRYPTO_UTILS_TEST_H

// GTest includes
#include "gtest/gtest.h"

// Poco includes
#include "Poco/Path.h"

// Local includes
#include "awsmock/core/FileUtils.h"
#include "awsmock/core/CryptoUtils.h"

#define TEST_STRING "The quick brown fox jumps over the lazy dog"
#define BASE64_TEST_STRING "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="

#define MD5_SUM          "9e107d9d372bb6826bd81d3542a419d6"
#define SHA1_SUM         "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"
#define SHA256_SUM       "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"
#define SHA256_SUM_EMPTY "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
#define SHA256_HMAC_SUM  "62025e1d8825e24f50410f8e9b8c40c319f622244baab30265de1d5ee8bf6a19"

namespace AwsMock::Core {
  class CryptoTest : public ::testing::Test {};

  TEST_F(CryptoTest, Md5StringTest) {

    // arrange

    // act
    std::string result = Crypto::GetMd5FromString(TEST_STRING);

    // assert
    EXPECT_TRUE(result == MD5_SUM);
  }

  TEST_F(CryptoTest, Md5FileTest) {
    // arrange
    std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

    // act
    std::string result = Crypto::GetMd5FromFile(file);

    // assert
    EXPECT_TRUE(result== MD5_SUM);
  }

  TEST_F(CryptoTest, Md5DoubleFileTest) {
    // arrange
    std::string file1 = FileUtils::CreateTempFile("txt", TEST_STRING);
    std::string file2 = FileUtils::CreateTempFile("txt", TEST_STRING);

    // act
    std::string result1 = Crypto::GetMd5FromFile(file1);
    std::string result2 = Crypto::GetMd5FromFile(file2);

    // assert
    EXPECT_TRUE(result1 == result2);
  }

  TEST_F(CryptoTest, Sha1StringTest) {
    // arrange

    // act
    std::string result = Crypto::GetSha1FromString(TEST_STRING);

    // assert
    EXPECT_EQ(result, SHA1_SUM);
  }

  TEST_F(CryptoTest, Sha1FileTest) {
    // arrange
    std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

    // act
    std::string result = Crypto::GetSha1FromFile(file);

    // assert
    EXPECT_EQ(result, SHA1_SUM);
  }

  TEST_F(CryptoTest, Sha256StringTest) {
    // arrange

    // act
    std::string result = Crypto::GetSha256FromString(TEST_STRING);

    // assert
    EXPECT_EQ(result, SHA256_SUM);
  }

  TEST_F(CryptoTest, Sha256EmptyStringTest) {
    // arrange

    // act
    std::string result = Crypto::GetSha256FromString("");

    // assert
    EXPECT_EQ(result, SHA256_SUM_EMPTY);
  }

  TEST_F(CryptoTest, Sha256FileTest) {
    // arrange
    std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

    // act
    std::string result = Crypto::GetSha256FromFile(file);

    // assert
    EXPECT_EQ(result, SHA256_SUM);
  }

  TEST_F(CryptoTest, GetHmacSha256Test) {
    // arrange

    // act
    std::string result = Crypto::GetHmacSha256FromString("secretKey", TEST_STRING);

    // assert
    EXPECT_EQ(result, "6a7323506a6493e320d27b6eb5c64e722a314e15ddb753c837738e0c174cdb03");
  }

  TEST_F(CryptoTest, Aes256EncryptionText) {

    // arrange
    std::string testText = "This is a super secure text";
    std::string key = "TestKey";
    int len = (int)testText.length();

    // act
    unsigned char* result1 = Crypto::Aes256EncryptString((unsigned char *) testText.c_str(), &len, key);
    unsigned char* result2 = Crypto::Aes256DecryptString(result1, &len, key);

    // assert
    EXPECT_TRUE(strcasecmp(reinterpret_cast<const char *>(result2), reinterpret_cast<const char *>(result1)));
  }

  TEST_F(CryptoTest, Aes256EncryptionBase64Text) {

    // arrange
    std::string testText = "This is a super secure text";
    std::string key = "TestKey";
    int len = (int)testText.length();

    // act
    std::string result1 = Core::Crypto::Base64Encode(Crypto::Aes256EncryptString((unsigned char *) testText.c_str(), &len, key));
    std::string decoded = Core::Crypto::Base64Decode(result1);
    std::string result2 = std::string(reinterpret_cast<char*>(Crypto::Aes256DecryptString((unsigned char *) decoded.c_str(), &len, key)));

    // assert
    EXPECT_TRUE(Core::StringUtils::Equals(result2, testText));
  }

  TEST_F(CryptoTest, Base64EncodeTest) {
    // arrange

    // act
    std::string result = Crypto::Base64Encode(TEST_STRING);

    // assert
    EXPECT_EQ(result, BASE64_TEST_STRING);
  }

  TEST_F(CryptoTest, Base64DecodeTest) {
    // arrange

    // act
    std::string result = Crypto::Base64Decode(BASE64_TEST_STRING);

    // assert
    EXPECT_EQ(result, TEST_STRING);
  }

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_CRYPTO_UTILS_TEST_H