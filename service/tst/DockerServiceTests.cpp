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

#define NAME "test-container"
#define IMAGE "test-image:latest"

namespace AwsMock::Service {

    class DockerServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
      }

      Core::Configuration _configuration = Core::Configuration("/tmp/aws-mock.properties");
      DockerService _service = DockerService(_configuration);
    };

    TEST_F(DockerServiceTest, CreateContainerDtoTest) {

        // arrange
        std::string exposedPorts = "8080/tcp";
        std::string domainName = std::string(NAME) + ".dockerhost.net";
        std::vector<std::string> environment = {"ENVIRONMENT=localstack", "JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack"};

        // act
        Dto::Docker::CreateContainerRequest request = {.hostName=NAME, .domainName=domainName, .user="root", .image=IMAGE,
            .environment=environment, .exposedPorts=exposedPorts};
        std::string jsonString = request.ToJson();

        // assert
        EXPECT_FALSE(jsonString.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(jsonString, "\"Env\":[\"ENVIRONMENT=localstack\",\"JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack\"]"));
        EXPECT_TRUE(Core::StringUtils::Contains(jsonString, "\"ExposedPorts\":{\"8080/tcp\":{}}"));
    }


} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSSERVICETEST_H