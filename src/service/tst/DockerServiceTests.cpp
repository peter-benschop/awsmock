//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSSERVICETEST_H
#define AWMOCK_CORE_SQSSERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/service/common/DockerService.h"
#include <awsmock/core/Configuration.h>

// Test includes
#include <awsmock/core/TestUtils.h>

namespace AwsMock::Service {

    class DockerServiceTest : public ::testing::Test {

          protected:
        void SetUp() override {
        }

        void TearDown() override {
            Dto::Docker::Image image = _service.GetImageByName("hello-world", "latest");
            _service.DeleteImage(image.id);
            _service.PruneContainers();
        }

        Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
        DockerService _service = DockerService(_configuration);
    };

    TEST_F(DockerServiceTest, ImageExistsTest) {

        // arrange
        _service.CreateImage("hello-world", "latest", "hello-world");

        // act
        bool result = _service.ImageExists("hello-world", "latest");

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(DockerServiceTest, ContainerExistsTest) {

        // arrange
        const std::vector<std::string> environment;
        _service.CreateImage("hello-world", "latest", "hello-world");
        _service.CreateContainer("hello-world", "latest", environment, 1025);

        // act
        bool result = _service.ContainerExists("hello-world", "latest");

        // assert
        EXPECT_TRUE(result);
    }

}// namespace AwsMock::Service

#endif// AWMOCK_CORE_SQSSERVICETEST_H