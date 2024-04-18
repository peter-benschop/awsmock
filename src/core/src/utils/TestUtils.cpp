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
    ofs << "awsmock.region=eu-central-1";
    ofs << "awsmock.account.userPoolId=000000000000";
    ofs << "awsmock.client.userPoolId=00000000";
    ofs << "awsmock.user=none";
    ofs << "awsmock.data.dir=/tmp/awsmock/data";
    // Rest configuration
    ofs << "awsmock.service.gateway.host=" << hostName;
    ofs << "awsmock.service.gateway.port=" << port;
    // Database configuration
    ofs << "awsmock.mongodb.active=" << (withDatabase ? "true" : "false");
    ofs << "awsmock.mongodb.name=test";
    ofs << "awsmock.mongodb.host=" << hostName;
    ofs << "awsmock.mongodb.port=27017";
    ofs << "awsmock.mongodb.user=admin";
    ofs << "awsmock.mongodb.password=admin";
    // S3 configuration
    ofs << "awsmock.service.s3.port=19500";
    ofs << "awsmock.service.s3.host=localhost";
    ofs << "awsmock.monitoring.s3.period=-1";
    // S3 api configuration
    ofs << "awsmock.service.s3api.port=19501";
    ofs << "awsmock.service.s3api.host=localhost";
    ofs << "awsmock.monitoring.s3api.period=-1";
    // SQS configuration
    ofs << "awsmock.service.sqs.port=19502";
    ofs << "awsmock.service.sqs.host=" << hostName;
    ofs << "awsmock.monitoring.sqs.period=-1";
    // SQS configuration
    ofs << "awsmock.service.sns.port=19503";
    ofs << "awsmock.service.sns.host=" << hostName;
    ofs << "awsmock.monitoring.sns.period=-1";
    // Lambda configuration
    ofs << "awsmock.service.lambda.active=true";
    ofs << "awsmock.service.lambda.port=19504";
    ofs << "awsmock.service.lambda.host=localhost";
    ofs << "awsmock.monitoring.lambda.period=-1";
    // Transfer configuration
    ofs << "awsmock.service.transfer.active=true";
    ofs << "awsmock.service.transfer.port=19505";
    ofs << "awsmock.service.transfer.host=localhost";
    ofs << "awsmock.monitoring.transfer.period=-1";
    // Cognito configuration
    ofs << "awsmock.service.cognito.active=true";
    ofs << "awsmock.service.cognito.port=19506";
    ofs << "awsmock.service.cognito.host=localhost";
    ofs << "awsmock.monitoring.cognito.period=-1";
    // Cognito configuration
    ofs << "awsmock.service.dynamodb.active=true";
    ofs << "awsmock.service.dynamodb.port=19507";
    ofs << "awsmock.service.dynamodb.host=localhost";
    ofs << "awsmock.monitoring.dynamodb.period=-1";
    ofs << "awsmock.dynamodb.port=8000";
    // Docker
    ofs << "awsmock.docker.network.mode=bridge";
    ofs << "awsmock.docker.network.name=.dockerhost.net";
    ofs << "awsmock.docker.default.memory.size=512";
    ofs << "awsmock.docker.default.temp.size=10240";
    ofs << "awsmock.docker.container.port=8080";
    // Monitoring configuration
    ofs << "awsmock.monitoring.port=9100";
    // Logging
    ofs << "awsmock.log.level=debug";
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