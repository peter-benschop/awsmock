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

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            const std::string _port = _configuration.GetValueString("awsmock.modules.ssm.http.port");
            const std::string _host = _configuration.GetValueString("awsmock.modules.ssm.http.host");

            // Set test config
            _configuration.SetValueString("awsmock.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
        }

        void TearDown() override {
            _ssmDatabase.DeleteAllParameters();
        }

        std::string _endpoint;
        boost::asio::io_service _ios{10};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::SSMDatabase &_ssmDatabase = Database::SSMDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(SSMServerCliTest, ParameterPutTest) {

        // arrange

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();

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
        Core::ExecResult getResult = Core::TestUtils::SendCliCommand("aws ssm get-parameter --name " + TEST_PARAMETER_NAME + " --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, getResult.status);
        EXPECT_EQ(1, parameterList.size());
        EXPECT_TRUE(Core::StringUtils::Contains(getResult.output, TEST_PARAMETER_NAME));
    }

    TEST_F(SSMServerCliTest, ParameterDescribeTest) {

        // arrange
        Core::ExecResult putResult = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();
        EXPECT_EQ(1, parameterList.size());

        // act
        Core::ExecResult describeResult = Core::TestUtils::SendCliCommand("aws ssm describe-parameters --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, describeResult.status);
        EXPECT_TRUE(Core::StringUtils::Contains(describeResult.output, TEST_PARAMETER_NAME));
    }

    TEST_F(SSMServerCliTest, ParameterDeleteTest) {

        // arrange
        Core::ExecResult putResult = Core::TestUtils::SendCliCommand("aws ssm put-parameter --name " + TEST_PARAMETER_NAME + " --value " + TEST_PARAMETER_VALUE + " --endpoint " + _endpoint);
        Database::Entity::SSM::ParameterList parameterList = _ssmDatabase.ListParameters();
        EXPECT_EQ(1, parameterList.size());

        // act
        Core::ExecResult deleteResult = Core::TestUtils::SendCliCommand("aws ssm delete-parameter --name " + TEST_PARAMETER_NAME + " --endpoint " + _endpoint);
        parameterList = _ssmDatabase.ListParameters();

        // assert
        EXPECT_EQ(0, deleteResult.status);
        EXPECT_EQ(0, parameterList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H