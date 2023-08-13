//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_TARUTILSTEST_H
#define AWSMOCK_CORE_TARUTILSTEST_H

// GTest includes
#include "gtest/gtest.h"

// Poco includes
#include "Poco/Path.h"

// Local includes
#include "awsmock/core/TarUtils.h"
#include "awsmock/core/FileUtils.h"

namespace AwsMock::Core
{
    class TarUtilsTest : public ::testing::Test
    {

    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    TEST_F(TarUtilsTest, CompressTestTest)
    {
        // arrange
        std::string tempFile = FileUtils::GetTempFile("tgz");

        // act
        TarUtils::TarDirectory(tempFile, "/tmp/tmp/tartest");

        // assert
        int i = 0;
        //EXPECT_EQ(result, MD5_SUM);
    }


} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_TARUTILSTEST_H