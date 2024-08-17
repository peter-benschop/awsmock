//
// Created by vogje01 on 01/09/2022.
//

// C++ include
#include <fstream>

// GTest includes
#include <gtest/gtest.h>

// Test includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/service/docker/DockerService.h>
#include <awsmock/utils/TestUtils.h>

#define TEST_CONTAINER_NAME std::string("jensvogt/awsmock-test")
#define TEST_CONTAINER_VERSION std::string("latest")

class TestEnvironment : public ::testing::Environment {

  public:

    // Initialise a test configuration.
    void SetUp() override {

        AwsMock::Core::TestUtils::CreateTestConfigurationFile(false);
        AwsMock::Database::TestUtils::CreateServices();

        // Check image
        if (!dockerService.ImageExists(TEST_CONTAINER_NAME, TEST_CONTAINER_VERSION)) {
            dockerService.CreateImage(TEST_CONTAINER_NAME, TEST_CONTAINER_VERSION, TEST_CONTAINER_NAME);
        }

        // Check container
        if (!dockerService.ContainerExists(TEST_CONTAINER_NAME, TEST_CONTAINER_VERSION)) {
            AwsMock::Dto::Docker::CreateContainerResponse response = dockerService.CreateContainer(TEST_CONTAINER_NAME, TEST_CONTAINER_VERSION, 10100, 10100);
        }

        // Get docker container
        AwsMock::Dto::Docker::Container container = dockerService.GetContainerByName(TEST_CONTAINER_NAME, TEST_CONTAINER_VERSION);

        // Start docker container, in case it is not already running.
        if (container.state != "running") {
            dockerService.StartDockerContainer(container.id);
            log_info << "Test docker container started";
        } else {
            log_info << "Test docker container already running";
        }
    }

  private:

    AwsMock::Service::DockerService dockerService = AwsMock::Service::DockerService::instance();
};

int main(int argc, char **argv) {

    // Run data
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    int ret = RUN_ALL_TESTS();

    return ret;
}