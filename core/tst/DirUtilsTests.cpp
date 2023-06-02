//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_DIRUTILSTEST_H
#define AWMOCK_CORE_DIRUTILSTEST_H

// GTest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poco includes
#include "Poco/Path.h"
#include "Poco/File.h"

// Local includes
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>

#define FILE_SIZE (100*1024)

namespace AwsMock::Core {

    class DirUtilsTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
      }

    };

    TEST_F(DirUtilsTest, DeleteDirTest) {

        // arrange
        std::string dirName = DirUtils::CreateTempDir();

        // act
        EXPECT_NO_THROW({ DirUtils::DeleteDirectory(dirName); });

        // assert
        EXPECT_FALSE(DirUtils::DirectoryExists(dirName));
    }

    TEST_F(DirUtilsTest, DeleteDirRecursiveTest) {

        // arrange
        std::string dirName = DirUtils::CreateTempDir();
        for (int i = 0; i < 3; i++) {
            FileUtils::CreateTempFile(dirName, "json", 100);
        }

        // act
        EXPECT_NO_THROW({ DirUtils::DeleteDirectory(dirName, true); });

        // assert
        EXPECT_FALSE(DirUtils::DirectoryExists(dirName));
    }

    TEST_F(DirUtilsTest, DirectoryFileCountTest) {

        // arrange
        std::string dirName = DirUtils::CreateTempDir();
        for (int i = 0; i < 3; i++) {
            FileUtils::CreateTempFile(dirName, "json", 100);
        }

        // act
        long result = 0;
        EXPECT_NO_THROW({ result = DirUtils::DirectoryCountFiles(dirName); });

        // assert
        EXPECT_EQ(result, 3);
    }

    TEST_F(DirUtilsTest, DirectoryEmptyTest) {

        // arrange
        std::string dirName = DirUtils::CreateTempDir();

        // act
        bool result = false;
        EXPECT_NO_THROW({ result = DirUtils::DirectoryEmpty(dirName); });

        // assert
        EXPECT_EQ(result, true);
    }

    TEST_F(DirUtilsTest, ListFilesTest)
    {
        // arrange
        std::string dirName = DirUtils::CreateTempDir();
        std::string fileName1 = FileUtils::CreateTempFile(dirName, "json", 100);
        std::string fileName2 = FileUtils::CreateTempFile(dirName, "txt", 100);
        std::string fileName3 = FileUtils::CreateTempFile(dirName, "xml", 100);

        // act
        std::vector<std::string> result;
        EXPECT_NO_THROW({ result = DirUtils::ListFiles(dirName); });

        // assert
        EXPECT_FALSE(result.empty());
        std::string basename1 = FileUtils::StripBasePath(fileName1);
        std::string basename2 = FileUtils::StripBasePath(fileName2);
        std::string basename3 = FileUtils::StripBasePath(fileName3);
        EXPECT_THAT(result, ::testing::Contains(::testing::Eq(::std::string(basename1))));
        EXPECT_THAT(result, ::testing::Contains(::testing::Eq(::std::string(basename2))));
        EXPECT_THAT(result, ::testing::Contains(::testing::Eq(::std::string(basename3))));
    }

    TEST_F(DirUtilsTest, ListFilesPatternTest)
    {
        // arrange
        std::string dirName = DirUtils::CreateTempDir();
        std::string fileName1 = FileUtils::CreateTempFile(dirName, "json", 100);
        std::string fileName2 = FileUtils::CreateTempFile(dirName, "txt", 100);
        std::string fileName3 = FileUtils::CreateTempFile(dirName, "xml", 100);

        // act
        std::vector<std::string> result;
        EXPECT_NO_THROW({ result = DirUtils::ListFiles(dirName, "^.*\\.(json|xml)$"); });

        // assert
        EXPECT_FALSE(result.empty());
        EXPECT_EQ(result.size(), 2);
        std::string basename1 = FileUtils::StripBasePath(fileName1);
        std::string basename2 = FileUtils::StripBasePath(fileName3);
        EXPECT_THAT(result, ::testing::Contains(::testing::Eq(::std::string(basename1))));
        EXPECT_THAT(result, ::testing::Contains(::testing::Eq(::std::string(basename2))));
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H