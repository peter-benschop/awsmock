//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_DIRECTORYWATCHERTEST_H
#define AWSMOCK_CORE_DIRECTORYWATCHERTEST_H

// C++ standard includes
#include <string>
#include <future>
#include <algorithm>
#include <mutex>
#include <set>
#include <thread>

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include <Poco/Delegate.h>
#include <Poco/ThreadPool.h>

// AwsMock includes
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/DirectoryWatcher.h>
#include <awsmock/core/FileUtils.h>

namespace AwsMock::Core {

    class DirectoryWatcherTest : public ::testing::Test {

    protected:
      void SetUp() override {
          tempDir = DirUtils::CreateTempDir("/tmp");
          _watcher= std::make_shared<DirectoryWatcher>(tempDir);
          _watcher->itemAdded += Poco::delegate(this, &DirectoryWatcherTest::OnFileAdded);
          _watcher->itemModified += Poco::delegate(this, &DirectoryWatcherTest::OnFileModified);
          _watcher->itemDeleted += Poco::delegate(this, &DirectoryWatcherTest::OnFileDeleted);
      }

      void TearDown() override {
          thread->wakeUp();
          delete thread;
          DirUtils::DeleteDirectory(tempDir, true);
          added = 0;
          deleted = 0;
          modified = 0;
      }

    public:

      void OnFileAdded(const DirectoryEvent &addedEvent) {
          added++;
      }

      void OnFileModified(const DirectoryEvent &modifiedEvent) {
          modified++;
      }

      void OnFileDeleted(const DirectoryEvent &deletedEvent) {
          deleted++;
      }

      int added = 0, deleted = 0, modified = 0;
      std::shared_ptr<DirectoryWatcher> _watcher;
      std::string tempFile, tempDir;
      Poco::Thread *thread = new Poco::Thread();
    };

    /*TEST_F(DirectoryWatcherTest, FileAddedTest) {

        // arrange
        thread->start(*_watcher);

        // act
        tempFile = Core::FileUtils::CreateTempFile(tempDir, "txt", 10);

        // assert
        while (added == 0) {
            Poco::Thread::sleep(100);
        }
        EXPECT_TRUE(added == 1);
    }

    TEST_F(DirectoryWatcherTest, FileModifiedTest) {

        // arrange
        thread->start(*_watcher);

        // act
        tempFile = Core::FileUtils::CreateTempFile(tempDir, "txt", 10);
        std::ofstream ofs(tempFile, std::ios::app);
        ofs << "Test";

        // assert
        while (modified == 0) {
            Poco::Thread::sleep(100);
        }
        EXPECT_TRUE(modified == 1);
    }

    TEST_F(DirectoryWatcherTest, FileSeveralModifiedTest) {

        // arrange
        thread->start(*_watcher);

        // act
        tempFile = Core::FileUtils::CreateTempFile(tempDir, "txt", 10);
        std::ofstream ofs(tempFile, std::ios::app);
        ofs << "Test";

        // assert
        Poco::Thread::sleep(5000);
        EXPECT_TRUE(modified == 1);
    }

    TEST_F(DirectoryWatcherTest, FileDeletedTest) {

        // arrange
        thread->start(*_watcher);
        tempFile = Core::FileUtils::CreateTempFile(tempDir, "txt", 10);

        // act
        Core::FileUtils::DeleteFile(tempFile);

        // assert
        while (deleted == 0) {
            Poco::Thread::sleep(100);
        }
        EXPECT_TRUE(deleted == 1);
    }

    TEST_F(DirectoryWatcherTest, DirectoryAddedTest) {

        // arrange
        thread->StartServer(*_watcher);

        // act
        Core::DirUtils::MakeDirectory(tempDir + "/tmptest");

        // assert
        while (added == 0) {
            Poco::Thread::sleep(100);
        }
        EXPECT_TRUE(added == 1);
    }

    TEST_F(DirectoryWatcherTest, DirectoryDeleteTest) {

        // arrange
        thread->StartServer(*_watcher);
        Core::DirUtils::MakeDirectory(tempDir + "/tmptest");

        // act
        Core::DirUtils::DeleteDirectory(tempDir + "/tmptest");

        // assert
        while (deleted == 0) {
            Poco::Thread::sleep(100);
        }
        EXPECT_TRUE(deleted == 1);
    }*/
} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_DIRECTORYWATCHERTEST_H