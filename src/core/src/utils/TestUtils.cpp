//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/core/TestUtils.h>

namespace AwsMock::Core {

    void TestUtils::CreateTestConfigurationFile(bool withDatabase) {

        // Logging
        if (getenv("AWSMOCK_TEST_LOG") != nullptr) {
            LogStream::Initialize();
            LogStream::SetFilename("/tmp/awsmock-test.log");
            LogStream::SetSeverity("debug");
        } else {
            LogStream::Initialize();
            LogStream::SetSeverity("none");
        }

        constexpr int port = 14566;
        const std::string hostName = SystemUtils::GetNodeName();

        const YamlConfiguration config;
        config.SetValue("awsmock.region", "eu-central-1");
        config.SetValue("awsmock.access.account-id", "000000000000");
        config.SetValue("awsmock.access.client-id", "00000000");
        config.SetValue("awsmock.user", "none");
        config.SetValue("awsmock.data.dir", "/tmp/awsmock/data");
        config.SetValue("awsmock.gateway.active", true);
        config.SetValue("awsmock.gateway.host", hostName);
        config.SetValue("awsmock.gateway.port", port);
        config.SetValue("awsmock.gateway.address", "0.0.0.0");
        config.SetValue("awsmock.gateway.max-queue", 10);
        config.SetValue("awsmock.gateway.max-threads", 10);
        config.SetValue("awsmock.gateway.timeout", 10);
        /*
        // Mongo DB
        ofs << "awsmock.mongodb.active=" << (withDatabase ? "true" : "false") << std::endl;
        ofs << "awsmock.mongodb.name=test" << std::endl;
        ofs << "awsmock.mongodb.http.host=" << hostName << std::endl;
        ofs << "awsmock.mongodb.http.port=27017" << std::endl;
        ofs << "awsmock.mongodb.user=root" << std::endl;
        ofs << "awsmock.mongodb.password=password" << std::endl;
        // S3 configuration
        ofs << "awsmock.service.s3.http.port=19500" << std::endl;
        ofs << "awsmock.service.s3.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.s3.period=-1" << std::endl;
        // S3 api configuration
        ofs << "awsmock.service.s3api.http.port=19501" << std::endl;
        ofs << "awsmock.service.s3api.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.s3api.period=-1" << std::endl;
        // SQS configuration
        ofs << "awsmock.service.sqs.http.port=19502" << std::endl;
        ofs << "awsmock.service.sqs.http.host=" << hostName << std::endl;
        ofs << "awsmock.monitoring.sqs.period=-1" << std::endl;
        // SQS configuration
        ofs << "awsmock.service.sns.http.port=19503" << std::endl;
        ofs << "awsmock.service.sns.http.host=" << hostName << std::endl;
        ofs << "awsmock.monitoring.sns.period=-1" << std::endl;
        // Lambda configuration
        ofs << "awsmock.service.lambda.active=true" << std::endl;
        ofs << "awsmock.service.lambda.http.port=19504" << std::endl;
        ofs << "awsmock.service.lambda.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.lambda.period=-1" << std::endl;
        // Transfer configuration
        ofs << "awsmock.service.transfer.active=true" << std::endl;
        ofs << "awsmock.service.transfer.http.port=19505" << std::endl;
        ofs << "awsmock.service.transfer.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.transfer.period=-1" << std::endl;
        // Cognito configuration
        ofs << "awsmock.service.cognito.active=true" << std::endl;
        ofs << "awsmock.service.cognito.http.port=19506" << std::endl;
        ofs << "awsmock.service.cognito.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.cognito.period=-1" << std::endl;
        // Cognito configuration
        ofs << "awsmock.service.dynamodb.active=true" << std::endl;
        ofs << "awsmock.service.dynamodb.http.port=19507" << std::endl;
        ofs << "awsmock.service.dynamodb.http.host=localhost" << std::endl;
        ofs << "awsmock.monitoring.dynamodb.period=-1" << std::endl;
        ofs << "awsmock.dynamodb.port=8000" << std::endl;
        // Docker
        ofs << "awsmock.docker.network.mode=bridge" << std::endl;
        ofs << "awsmock.docker.network.name=.dockerhost.net" << std::endl;
        ofs << "awsmock.docker.default.memory.size=512" << std::endl;
        ofs << "awsmock.docker.default.temp.size=10240" << std::endl;
        ofs << "awsmock.docker.container.port=8080" << std::endl;
        // Monitoring configuration
        ofs << "awsmock.service.monitoring.port=9091" << std::endl;
        // Logging
        ofs << "awsmock.service.logging.level=debug" << std::endl;
        ofs << "awsmock.service.logging.file=/tmp/awsmock-test.log" << std::endl;
        ofs.close();*/
        //config.SetFilename(TMP_PROPERTIES_FILE);
        config.WriteFile(TMP_PROPERTIES_FILE);
    }

    std::string TestUtils::GetTestConfigurationFilename() {
        return TMP_PROPERTIES_FILE;
    }

    YamlConfiguration &TestUtils::GetTestConfiguration(bool withDatabase) {
        CreateTestConfigurationFile(withDatabase);
        YamlConfiguration &configuration = YamlConfiguration::instance();
        configuration.SetFilename(GetTestConfigurationFilename());
        return configuration;
    }

    ExecResult TestUtils::SendCliCommand(const std::string &command) {
        return SystemUtils::Exec(command);
    }

}// namespace AwsMock::Core