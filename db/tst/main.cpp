//
// Created by vogje01 on 01/09/2022.
//

// GTest includes
#include "gtest/gtest.h"

// AwsMock includes
#include <awsmock/core/FileUtils.h>

class TestEnvironment : public ::testing::Environment {
public:

  // Initialise a test configuration.
  void SetUp() override {
      std::ofstream ofs("/tmp/aws-mock.properties");
      ofs << "awsmock.region=eu-central-1" << std::endl;
      ofs << "awsmock.rest.host=localhost" << std::endl;
      ofs << "awsmock.rest.port=4567" << std::endl;
      ofs << "awsmock.data.dir=/tmp/test/data" << std::endl;
      ofs << "awsmock.db.dir=/tmp/test/data/db" << std::endl;
      ofs << "awsmock.db.file=awsmock.db" << std::endl;
      ofs << "awsmock.threadpool.name=srv-worker" << std::endl;
      ofs << "awsmock.threadpool.min=8" << std::endl;
      ofs << "awsmock.threadpool.max=32" << std::endl;
      ofs << "awsmock.threadpool.idletime=60" << std::endl;
      ofs << "awsmock.monitoring.port=8081" << std::endl;
      ofs << "awsmock.monitoring.timeout=60000" << std::endl;
      ofs << "awsmock.log.level=debug" << std::endl;
  }
};

int main(int argc, char **argv) {

    // Run tests
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    int ret = RUN_ALL_TESTS();

    return ret;
}