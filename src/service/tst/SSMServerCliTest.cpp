//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H
#define AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/SSMDatabase.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/ssm/SSMServer.h>

#define TEST_PARAMETER_NAME std::string("test-name")
#define TEST_PARAMETER_VALUE std::string("test-value")

namespace AwsMock::Service {

    class SSMServerCliTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // General configuration
            _region = _configuration.GetValueString("awsmock.region");

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            const std::string _port = _configuration.GetValueString("awsmock.gateway.http.port");
            const std::string _host = _configuration.GetValueString("awsmock.gateway.http.host");
            const std::string _address = _configuration.GetValueString("awsmock.gateway.http.address");

            // Set test config
            _endpoint = "http://" + _host + ":" + _port;

            // Start gateway server
            _gatewayServer = std::make_shared<GatewayServer>(_ios);
            _thread = boost::thread([&]() {
                boost::asio::io_service::work work(_ios);
                _ios.run();
            });
        }

        void TearDown() override {
            _ssmDatabase.DeleteAllParameters();
        }

        boost::thread _thread;
        std::string _endpoint, _region;
        boost::asio::io_service _ios{10};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::SSMDatabase &_ssmDatabase = Database::SSMDatabase::instance();
        std::shared_ptr<GatewayServer> _gatewayServer;
    };

    TEST_F(SSMServerCliTest, ParameterPutTest) {

        // arrange

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        const Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();

        // assert
        EXPECT_EQ(0, status);
        EXPECT_EQ(1, parameterList.size());
        EXPECT_TRUE(Core::StringUtils::Contains(output, "Version"));
    }

    TEST_F(SSMServerCliTest, ParameterGetTest) {

        // arrange
        Core::ExecResult putResult = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        const Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();
        EXPECT_EQ(1, parameterList.size());

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws ssm get-parameter --name " + TEST_PARAMETER_NAME + " --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, status);
        EXPECT_EQ(1, parameterList.size());
        EXPECT_TRUE(Core::StringUtils::Contains(output, TEST_PARAMETER_NAME));
    }

    TEST_F(SSMServerCliTest, ParameterDescribeTest) {

        // arrange
        Core::ExecResult putResult = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();
        EXPECT_EQ(1, parameterList.size());

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws ssm describe-parameters --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, status);
        EXPECT_TRUE(Core::StringUtils::Contains(output, TEST_PARAMETER_NAME));
    }

    TEST_F(SSMServerCliTest, ParameterDeleteTest) {

        // arrange
        Core::ExecResult putResult = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();
        EXPECT_EQ(1, parameterList.size());

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws ssm delete-parameter --name " + TEST_PARAMETER_NAME + " --endpoint " + _endpoint);
        parameterList = _ssmDatabase.ListParameters();

        // assert
        EXPECT_EQ(0, status);
        EXPECT_EQ(0, parameterList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H