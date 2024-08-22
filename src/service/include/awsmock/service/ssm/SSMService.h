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
#include <awsmock/dto/ssm/PutParameterRequest.h>
#include <awsmock/dto/ssm/PutParameterResponse.h>
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
         * Constructor
         */
        explicit SSMService();

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

        /**
         * Creates a new key
         *
         * @param request create key request
         * @return CreateKeyResponse
         * @see Dto::KMS::CreateKeyRequest
         * @see Dto::KMS::CreateKeyResponse
         */
        //Dto::KMS::CreateKeyResponse CreateKey(const Dto::KMS::CreateKeyRequest &request);

        /**
         * @brief Wait for the asynchronous key creation
         *
         * @param keyId key ID
         * @param maxSeconds maximal seconds
         */
        //void WaitForRsaKey(const std::string &keyId, int maxSeconds);

        /**
         * @brief Wait for the asynchronous key creation
         *
         * @param keyId key ID
         * @param maxSeconds maximal seconds
         */
        //void WaitForAesKey(const std::string &keyId, int maxSeconds);

        /**
         * Schedules a key deletion
         *
         * @param request create queue request
         * @return ScheduleKeyDeletionRequest
         * @throws Core::DatabaseException
         * @see Dto::KMS::ScheduledKeyDeletionResponse
         */
        //Dto::KMS::ScheduledKeyDeletionResponse ScheduleKeyDeletion(const Dto::KMS::ScheduleKeyDeletionRequest &request);

        /**
         * Describe a key
         *
         * @param request describe key request
         * @return DescribeKeyResponse
         * @throws Core::DatabaseException
         * @see Dto::KMS::DescribeKeyRequest
         * @see Dto::KMS::DescribeKeyResponse
         */
        //Dto::KMS::DescribeKeyResponse DescribeKey(const Dto::KMS::DescribeKeyRequest &request);

        /**
         * Encrypt a plain text using a given algorithm
         *
         * @param request encrypt request
         * @return EncryptResponse
         * @throws Core::DatabaseException, Core::ServiceException
         * @see Dto::KMS::EncryptRequest
         * @see Dto::KMS::EncryptResponse
         */
        //Dto::KMS::EncryptResponse Encrypt(const Dto::KMS::EncryptRequest &request);

        /**
         * Decrypts a cipher text using a given algorithm
         *
         * @param request decrypt request
         * @return DecryptResponse
         * @throws Core::DatabaseException, Core::ServiceException
         * @see Dto::KMS::DecryptRequest
         * @see Dto::KMS::DecryptResponse
         */
        //Dto::KMS::DecryptResponse Decrypt(const Dto::KMS::DecryptRequest &request);

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
