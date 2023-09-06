//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSSERVICETEST_H
#define AWMOCK_CORE_SQSSERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/service/DockerService.h>

// Test includes
#include "TestCommon.h"

#define NAME "test-container"
#define IMAGE "test-image:latest"

namespace AwsMock::Service {

    class DockerServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
      }

      Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
      DockerService _service = DockerService(_configuration);
    };

    TEST_F(DockerServiceTest, ImageExistsTest) {

        // arrange

        // act
        bool result = _service.ImageExists("name", "tag");

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(DockerServiceTest, ImageCreateTest) {

        // arrange

        // act
        _service.CreateImage("name", "latest", "hello-world");
        Dto::Docker::Image image = _service.GetImageByName("name", "latest");

        // assert
        EXPECT_TRUE(image.id.empty());
    }

    TEST_F(DockerServiceTest, ImageGetByNameTest) {

        // arrange

        // act
        Dto::Docker::Image image = _service.GetImageByName("name", "tag");

        // assert
        EXPECT_TRUE(image.id.empty());
    }

    TEST_F(DockerServiceTest, ContainerExistsTest) {

        // arrange

        // act
        bool result = _service.ContainerExists("name", "tag");

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(DockerServiceTest, ContainerCreateDtoTest) {

        // arrange
        std::string exposedPorts = CONTAINER_PORT;
        std::string domainName = std::string(NAME) + NETWORK_NAME;
        std::vector<std::string>
            environment = {"AWS_EC2_METADATA_DISABLED=true", "JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack"};

        // act
        Dto::Docker::CreateContainerRequest request = {
            .hostName=NAME,
            .domainName=domainName,
            .user="root",
            .image=IMAGE,
            .environment=environment,
            .containerPort=exposedPorts};
        std::string jsonString = request.ToJson();

        // assert
        EXPECT_FALSE(jsonString.empty());
        EXPECT_TRUE(Core::StringUtils::Equals(jsonString,
                                              R"({"Domainname":"test-container.dockerhost.net","Env":["AWS_EC2_METADATA_DISABLED=true","JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack"],"ExposedPorts":{"8080/tcp":{}},"HostConfig":{"ExtraHosts":["host.docker.internal:host-gateway","localstack:host-gateway"],"NetworkMode":"","PortBindings":{"8080/tcp":[{"HostPort":""}]}},"Hostname":"test-container","Image":"test-image:latest","User":"root"})"));
    }
} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSSERVICETEST_H