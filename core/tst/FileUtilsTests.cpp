#ifndef AWMOCK_CORE_FILEUTILSTEST_H
#define AWMOCK_CORE_FILEUTILSTEST_H

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

namespace AwsMock::Core
{
    class FileUtilsTest : public ::testing::Test
    {

    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    TEST_F(FileUtilsTest, BasenameTest)
    {
        // arrange
        std::string fileName = "/tmp/example.gif";

        // act
        std::string result = FileUtils::GetBasename(fileName);

        // assert
        EXPECT_EQ(result.length(), 7);
        EXPECT_EQ(result, "example");
    }

    TEST_F(FileUtilsTest, ExtensionTest)
    {
        // arrange
        std::string fileName = FileUtils::CreateTempFile("gif");

        // act
        std::string result = FileUtils::GetExtension(fileName);

        // assert
        EXPECT_EQ(result.length(), 3);
        EXPECT_EQ(result, "gif");
    }

    TEST_F(FileUtilsTest, FileSizeTest)
    {
        // arrange
        std::string fileName = FileUtils::CreateTempFile("gif", 100);

        // act
        long result = FileUtils::FileSize(fileName);

        // assert
        EXPECT_EQ(result, 100);
    }

    TEST_F(FileUtilsTest, DeleteFileTest)
    {
        // arrange
        std::string fileName = FileUtils::CreateTempFile("gif");

        // act
        EXPECT_NO_THROW({ FileUtils::DeleteFile(fileName); });

        // assert
        EXPECT_FALSE(FileUtils::FileExists(fileName));
    }

    TEST_F(FileUtilsTest, StripBasenameTest)
    {
        // arrange
        std::string fileName = "/tmp/testFile.txt";

        // act
        std::string basename;
        EXPECT_NO_THROW({ basename = FileUtils::StripBasePath(fileName); });

        // assert
        EXPECT_FALSE(basename.empty());
        EXPECT_STREQ(basename.c_str(), "testFile.txt");
    }

    TEST_F(FileUtilsTest, CompressTest)
    {
        // arrange
        std::string zipName = FileUtils::GetTempFile("zip");
        std::string dirName = DirUtils::CreateTempDir();
        for (int i = 0; i < 3; i++)
        {
            FileUtils::CreateTempFile(dirName, "json", 100);
        }

        // act
        EXPECT_NO_THROW({ FileUtils::zipFiles(zipName, dirName); });

        // assert
        EXPECT_TRUE(FileUtils::FileExists(zipName));
        EXPECT_TRUE(FileUtils::FileSize(zipName) > 0);
    }

    TEST_F(FileUtilsTest, UncompressTest)
    {
        // arrange
        std::string zipName = FileUtils::GetTempFile("zip");
        std::string dirName = DirUtils::CreateTempDir();
        std::string outputDirName = DirUtils::CreateTempDir();
        for (int i = 0; i < 3; i++)
        {
            FileUtils::CreateTempFile(dirName, "json", 100);
        }

        // act
        EXPECT_NO_THROW({ FileUtils::zipFiles(zipName, dirName); });
        EXPECT_NO_THROW({ FileUtils::unzipFiles(zipName, outputDirName); });

        // assert
        EXPECT_TRUE(DirUtils::DirectoryExists(outputDirName));
        EXPECT_FALSE(DirUtils::DirectoryEmpty(outputDirName));
    }

    TEST_F(FileUtilsTest, CreateTempFileTest)
    {
        // arrange

        // act
        std::string tempFile = FileUtils::CreateTempFile("json", FILE_SIZE);

        // assert
        EXPECT_FALSE(tempFile.empty());
        EXPECT_TRUE(FileUtils::FileExists(tempFile));
        EXPECT_EQ(FILE_SIZE, FileUtils::FileSize(tempFile));
    }

} // namespace AwsMOck::Core

#endif // AWMOCK_CORE_FILEUTILSTEST_H