//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_RANDOM_UTILS_TEST_H
#define AWSMOCK_CORE_RANDOM_UTILS_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/RandomUtils.h>

namespace AwsMock::Core {

    class RandomUtilsTest : public ::testing::Test {};

    TEST_F(RandomUtilsTest, MinMaxIntTest) {

        // arrange
        int min = 32768;
        int max = 65536;

        // act
        std::vector<int> result;
        result.reserve(200);
        for (int i = 0; i < 100; i++) {
            result.emplace_back(RandomUtils::NextInt(min, max));
        }

        // assert
        for (int i = 0; i < 100; i++) {
            EXPECT_TRUE(result[i] >= min && result[i] <= max);
        }
        result.clear();
    }

    TEST_F(RandomUtilsTest, IntArrayTest) {

        // arrange
        int min = 32768;
        int max = 65536;
        int size = 100;

        // act
        std::vector<int> result = RandomUtils::IntArray(size, min, max);

        // assert
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(result[i] >= min && result[i] <= max);
        }
        result.clear();
    }

    TEST_F(RandomUtilsTest, MinMaxDoubleTest) {

        // arrange
        double min = 0.0;
        double max = 1.0;

        // act
        std::vector<double> result;
        result.reserve(100);
        for (int i = 0; i < 100; i++) {
            result.emplace_back(RandomUtils::NextDouble(min, max));
        }

        // assert
        for (int i = 0; i < 100; i++) {
            EXPECT_TRUE(result[i] > min && result[i] < max);
        }
        result.clear();
    }

    TEST_F(RandomUtilsTest, DoubleArrayTest) {

        // arrange
        double min = 0.0;
        double max = 1.0;
        int size = 100;

        // act
        std::vector<double> result = RandomUtils::DoubleArray(size, min, max);

        // assert
        for (int i = 0; i < size; i++) {
            EXPECT_TRUE(result[i] > min && result[i] < max);
        }
        result.clear();
    }

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_RANDOM_UTILS_TEST_H
