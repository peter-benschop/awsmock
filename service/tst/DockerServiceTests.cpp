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
#include <awsmock/core/TestUtils.h>

#define NAME "test-container"
#define IMAGE "test-image:latest"

namespace AwsMock::Service {

    class DockerServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
          _service.DeleteImage("hello-world", "latest");
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