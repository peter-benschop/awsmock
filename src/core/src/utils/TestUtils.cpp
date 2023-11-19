//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/core/TestUtils.h>

namespace AwsMock::Core {

  void TestUtils::CreateTestConfigurationFile() {
    int port = SystemUtils::GetRandomPort();
    std::string hostName = SystemUtils::GetNodeName();
    std::ofstream ofs(TMP_PROPERTIES_FILE, std::ofstream::out | std::ofstream::trunc);
    // AWS configuration
    ofs << "awsmock.region=eu-central-1" << std::endl;
    ofs << "awsmock.account.id=000000000000" << std::endl;
    ofs << "awsmock.client.id=00000000" << std::endl;
    ofs << "awsmock.user=none" << std::endl;
    // Rest configuration
    ofs << "awsmock.service.gateway.host=" << hostName << std::endl;
    ofs << "awsmock.service.gateway.port=" << port << std::endl;
    // Database configuration
    ofs << "awsmock.mongodb.name=test" << std::endl;
    ofs << "awsmock.mongodb.host=" << hostName << std::endl;
    ofs << "awsmock.mongodb.port=27017" << std::endl;
    ofs << "awsmock.mongodb.user=admin" << std::endl;
    ofs << "awsmock.mongodb.password=admin" << std::endl;
    // S3 configuration
    ofs << "awsmock.module.s3.data.dir=/tmp/test/data/s3" << std::endl;
    ofs << "awsmock.module.s3.port=19500" << std::endl;
    ofs << "awsmock.module.s3.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.s3.period=-1" << std::endl;
    // SQS configuration
    ofs << "awsmock.module.sqs.port=19501" << std::endl;
    ofs << "awsmock.module.sqs.host=" << hostName << std::endl;
    ofs << "awsmock.monitoring.sqs.period=-1" << std::endl;
    // Thread pool configuration
    ofs << "awsmock.threadpool.name=srv-worker" << std::endl;
    ofs << "awsmock.threadpool.min=8" << std::endl;
    ofs << "awsmock.threadpool.max=32" << std::endl;
    ofs << "awsmock.threadpool.idletime=60" << std::endl;
    // Monitoring configuration
    ofs << "awsmock.monitoring.port=8081" << std::endl;
    // Logging
    ofs << "awsmock.log.level=error" << std::endl;
    // Docker
    ofs << "awsmock.docker.network.mode=bridge" << std::endl;
    ofs << "awsmock.docker.network.name=.dockerhost.net" << std::endl;
    ofs << "awsmock.docker.default.memory.size=512" << std::endl;
    ofs << "awsmock.docker.default.temp.size=10240" << std::endl;
    ofs << "awsmock.docker.container.port=8080" << std::endl;
    ofs.close();
  }
}