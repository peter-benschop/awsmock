//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_FILEWATCHERTEST_H
#define AWSMOCK_CORE_FILEWATCHERTEST_H

// C++ standard includes
#include <string>
#include <regex>
#include <future>
#include <algorithm>
#include <mutex>
#include <vector>
#include <set>
#include <thread>

// GTest includes
#include <gtest/gtest.h>

//#include "catch/catch.hpp"

#include <awsmock/core/FileWatcher.h>

using test_string = std::string;
using test_char = char *;
using test_regex = std::regex;

namespace AwsMock::Core {

    namespace config {
        // 3 second test timeout
        typedef std::chrono::duration<float, std::ratio_multiply<std::chrono::seconds::period, std::ratio<100>>> test_timeout;
    }

    template<typename T>
    static T GetWithTimeout(std::future<T> &future_to_wait_for) {
        const auto status = future_to_wait_for.wait_for(AwsMock::Core::config::test_timeout(1));
        EXPECT_NE(status, std::future_status::deferred);
        EXPECT_NE(status, std::future_status::timeout);
        if (status == std::future_status::ready) {
            return future_to_wait_for.get();
        } else {
            throw std::runtime_error("Timeout reached");
        }
    }

    template<typename T>
    static void CreateAndModifyFile(T &path) {
        std::ofstream file(path);
        file << "test" << std::endl;
        file.close();
    }

    class FileWatcherTest : public ::testing::Test {};

    TEST_F(FileWatcherTest, AddTest) {

        const auto test_folder_path = "./";
        const auto test_file_name = "test.txt";

        std::promise<test_string> promise;
        std::future<test_string> future = promise.get_future();
        AwsMock::Core::FileWatch<test_string> watch(test_folder_path, [&promise](const test_string &path, const AwsMock::Core::Event change_type) {
          promise.set_value(path);
        });

        AwsMock::Core::CreateAndModifyFile(test_file_name);

        auto path = AwsMock::Core::GetWithTimeout(future);
        EXPECT_STREQ(path.c_str(), test_file_name);
    }

    TEST_F(FileWatcherTest, SingleFileTest) {
        const auto test_folder_path = "./test.txt";
        const auto test_ignore_path = "./ignore.txt";
        const auto test_file_name = "test.txt";

        // Create the file otherwise the Filewatch will throw
        CreateAndModifyFile(test_file_name);

        std::promise<test_string> promise;
        std::future<test_string> future = promise.get_future();

        FileWatch<test_string> watch(test_folder_path, [&promise, &test_file_name](const test_string &path, const Event change_type) {
          EXPECT_STREQ(path.c_str(), test_file_name);
          promise.set_value(path);
        });

        CreateAndModifyFile(test_ignore_path);
        CreateAndModifyFile(test_file_name);

        auto path = GetWithTimeout(future);
        EXPECT_STREQ(path.c_str(), test_file_name);
    }

    TEST_F(FileWatcherTest, ConstructorTest) {
        const auto test_folder_path = "./";
        const auto test_file_name = "test.txt";

        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        std::vector<test_string> files_triggered;
        std::set<std::thread::id> file_watch_threads;
        std::mutex mutex;
        const auto expected_triggers = 2u;

        FileWatch<test_string> watch(test_folder_path,
                                     [&promise, &files_triggered, &file_watch_threads, &expected_triggers, &mutex](const test_string &path, const Event change_type) {
                                       std::lock_guard<std::mutex> lock(mutex);
                                       file_watch_threads.insert(std::this_thread::get_id());
                                       files_triggered.push_back(path);
                                       if (file_watch_threads.size() == expected_triggers) {
                                           promise.set_value();
                                       }
                                     });

        FileWatch<test_string> watch2(watch);

        CreateAndModifyFile(test_file_name);

        GetWithTimeout(future);
        const auto
            files_match = std::all_of(files_triggered.begin(), files_triggered.end(), [&test_file_name](const test_string &path) { return path == test_file_name; });
        EXPECT_TRUE(files_match);
    }

    TEST_F(FileWatcherTest, CopyOperatorTest) {
        const auto test_folder_path = "./";
        const auto test_file_name = "test.txt";

        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        std::vector<test_string> files_triggered;
        std::set<std::thread::id> file_watch_threads;
        std::mutex mutex;
        const auto expected_triggers = 2u;

        FileWatch<test_string> watch(test_folder_path,
                                     [&promise, &files_triggered, &file_watch_threads, &expected_triggers, &mutex](const test_string &path, const Event change_type) {
                                       std::lock_guard<std::mutex> lock(mutex);
                                       file_watch_threads.insert(std::this_thread::get_id());
                                       files_triggered.push_back(path);
                                       if (file_watch_threads.size() == expected_triggers) {
                                           promise.set_value();
                                       }
                                     });

        FileWatch<test_string> watch2 = watch;

        CreateAndModifyFile(test_file_name);

        GetWithTimeout(future);
        const auto
            files_match = std::all_of(files_triggered.begin(), files_triggered.end(), [&test_file_name](const test_string &path) { return path == test_file_name; });
        EXPECT_TRUE(files_match);
    }

    TEST_F(FileWatcherTest, RegexTest) {
        const auto test_folder_path = "./";
        const auto test_ignore_path = "./ignore.txt";
        const auto test_file_name = "test.txt";

        // create the file otherwise the Filewatch will throw
        CreateAndModifyFile(test_file_name);

        std::promise<test_string> promise;
        std::future<test_string> future = promise.get_future();

        FileWatch<test_string> watch(test_folder_path,
                                                 test_regex("test.*"),
                                                 [&promise, &test_file_name](const test_string &path, const Event change_type) {
                                                   EXPECT_STREQ(path.c_str(), test_file_name);
                                                   promise.set_value(path);
                                                 });

        CreateAndModifyFile(test_ignore_path);
        CreateAndModifyFile(test_file_name);

        auto path = GetWithTimeout(future);
        EXPECT_STREQ(path.c_str(), test_file_name);
    }

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_FILEWATCHERTEST_H