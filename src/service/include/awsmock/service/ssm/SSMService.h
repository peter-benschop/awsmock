//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_SSM_SERVICE_H
#define AWSMOCK_SERVICE_SSM_SERVICE_H

// C++ standard includes
#include <chrono>
#include <ctime>
#include <string>

// Poco includes
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/core/monitoring/MetricServiceTimer.h>
#include <awsmock/dto/ssm/GetParameterRequest.h>
#include <awsmock/dto/ssm/GetParameterResponse.h>
#include <awsmock/dto/ssm/PutParameterRequest.h>
#include <awsmock/dto/ssm/PutParameterResponse.h>
#include <awsmock/dto/ssm/mapper/Mapper.h>
#include <awsmock/repository/SSMDatabase.h>

#define DEFAULT_SSM_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    using std::chrono::system_clock;

    /**
     * @brief SSM service
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMService {

      public:

        /**
         * @brief Constructor
         */
        explicit SSMService();

        /**
         * @brief Creates a new key
         *
         * @param request create key request
         * @return CreateKeyResponse
         * @see Dto::KMS::CreateKeyRequest
         * @see Dto::KMS::CreateKeyResponse
         */
        Dto::SSM::PutParameterResponse PutParameter(const Dto::SSM::PutParameterRequest &request);

        /**
         * @brief Creates a new key
         *
         * @param request create key request
         * @return CreateKeyResponse
         * @see Dto::KMS::CreateKeyRequest
         * @see Dto::KMS::CreateKeyResponse
         */
        Dto::SSM::GetParameterResponse GetParameter(const Dto::SSM::GetParameterRequest &request);

        /**
         * List all keys
         *
         * @param request list queue request
         * @return ListKeysResponse
         * @throws Core::DatabaseException
         * @see Dto::KMS::ListKeysRequest
         * @see Dto::KMS::ListKeysResponse
         */
        //Dto::KMS::ListKeysResponse ListKeys(const Dto::KMS::ListKeysRequest &request);

      private:

        /**
         * Account ID
         */
        std::string _accountId;

        /**
         * Database connection
         */
        Database::SSMDatabase &_ssmDatabase;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_SERVICE_H
