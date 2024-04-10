//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/core/TestUtils.h>

namespace AwsMock::Core {

  void TestUtils::CreateTestConfigurationFile() {
    CreateTestConfigurationFile(true);
    Core::Configuration& configuration = Core::Configuration::instance();
    configuration.SetFilename(TMP_PROPERTIES_FILE);
  }

  void TestUtils::CreateTestConfigurationFile(bool withDatabase) {
    int port = SystemUtils::GetRandomPort();
    std::string hostName = SystemUtils::GetNodeName();
    std::ofstream ofs(TMP_PROPERTIES_FILE, std::ofstream::out | std::ofstream::trunc);
    // AWS configuration
    ofs << "awsmock.region=eu-central-1" << std::endl;
    ofs << "awsmock.account.userPoolId=000000000000" << std::endl;
    ofs << "awsmock.client.userPoolId=00000000" << std::endl;
    ofs << "awsmock.user=none" << std::endl;
    ofs << "awsmock.data.dir=/tmp/awsmock/data" << std::endl;
    // Rest configuration
    ofs << "awsmock.service.gateway.host=" << hostName << std::endl;
    ofs << "awsmock.service.gateway.port=" << port << std::endl;
    // Database configuration
    ofs << "awsmock.mongodb.active=" << (withDatabase ? "true" : "false") << std::endl;
    ofs << "awsmock.mongodb.name=test" << std::endl;
    ofs << "awsmock.mongodb.host=" << hostName << std::endl;
    ofs << "awsmock.mongodb.port=27017" << std::endl;
    ofs << "awsmock.mongodb.user=admin" << std::endl;
    ofs << "awsmock.mongodb.password=admin" << std::endl;
    // S3 configuration
    ofs << "awsmock.service.s3.port=19500" << std::endl;
    ofs << "awsmock.service.s3.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.s3.period=-1" << std::endl;
    // S3 api configuration
    ofs << "awsmock.service.s3api.port=19501" << std::endl;
    ofs << "awsmock.service.s3api.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.s3api.period=-1" << std::endl;
    // SQS configuration
    ofs << "awsmock.service.sqs.port=19502" << std::endl;
    ofs << "awsmock.service.sqs.host=" << hostName << std::endl;
    ofs << "awsmock.monitoring.sqs.period=-1" << std::endl;
    // SQS configuration
    ofs << "awsmock.service.sns.port=19503" << std::endl;
    ofs << "awsmock.service.sns.host=" << hostName << std::endl;
    ofs << "awsmock.monitoring.sns.period=-1" << std::endl;
    // Lambda configuration
    ofs << "awsmock.service.lambda.active=true" << std::endl;
    ofs << "awsmock.service.lambda.port=19504" << std::endl;
    ofs << "awsmock.service.lambda.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.lambda.period=-1" << std::endl;
    // Transfer configuration
    ofs << "awsmock.service.transfer.active=true" << std::endl;
    ofs << "awsmock.service.transfer.port=19505" << std::endl;
    ofs << "awsmock.service.transfer.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.transfer.period=-1" << std::endl;
    // Cognito configuration
    ofs << "awsmock.service.cognito.active=true" << std::endl;
    ofs << "awsmock.service.cognito.port=19506" << std::endl;
    ofs << "awsmock.service.cognito.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.cognito.period=-1" << std::endl;
    // Cognito configuration
    ofs << "awsmock.service.dynamodb.active=true" << std::endl;
    ofs << "awsmock.service.dynamodb.port=19507" << std::endl;
    ofs << "awsmock.service.dynamodb.host=localhost" << std::endl;
    ofs << "awsmock.monitoring.dynamodb.period=-1" << std::endl;
    ofs << "awsmock.dynamodb.port=8000" << std::endl;
    // Docker
    ofs << "awsmock.docker.network.mode=bridge" << std::endl;
    ofs << "awsmock.docker.network.name=.dockerhost.net" << std::endl;
    ofs << "awsmock.docker.default.memory.size=512" << std::endl;
    ofs << "awsmock.docker.default.temp.size=10240" << std::endl;
    ofs << "awsmock.docker.container.port=8080" << std::endl;
    // Monitoring configuration
    ofs << "awsmock.monitoring.port=8081" << std::endl;
    // Logging
    ofs << "awsmock.log.level=debug" << std::endl;
    ofs.close();
  }

  std::string TestUtils::GetTestConfigurationFilename() {
    return TMP_PROPERTIES_FILE;
  }

  Core::Configuration& TestUtils::GetTestConfiguration(bool withDatabase){
    CreateTestConfigurationFile(withDatabase);
    Core::Configuration& configuration = Core::Configuration::instance();
    configuration.SetFilename(GetTestConfigurationFilename());
    return configuration;
  }

  Core::ExecResult TestUtils::SendCliCommand(const std::string &command) {
    return Core::SystemUtils::Exec(command);
  }

}