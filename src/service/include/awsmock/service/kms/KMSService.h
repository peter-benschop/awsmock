//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_SERVICE_H
#define AWSMOCK_SERVICE_KMS_SERVICE_H

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
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/kms/CreateKeyRequest.h>
#include <awsmock/dto/kms/CreateKeyResponse.h>
#include <awsmock/dto/kms/Key.h>
#include <awsmock/dto/kms/ListKey.h>
#include <awsmock/dto/kms/ListKeysRequest.h>
#include <awsmock/dto/kms/ListKeysResponse.h>
#include <awsmock/dto/kms/ScheduleKeyDeletionRequest.h>
#include <awsmock/dto/kms/ScheduleKeyDeletionResponse.h>
#include <awsmock/repository/KMSDatabase.h>
#include <awsmock/service/kms/KMSCreator.h>

#define DEFAULT_KMS_ACCOUNT_ID "000000000000"
#define DEFAULT_PENDING_PERIOD 30

namespace AwsMock::Service {

    /**
     * KMS service
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSService {

      public:

        /**
         * Constructor
         *
         * @param configuration module configuration
         */
        explicit KMSService(Core::Configuration &configuration);

        /**
         * List all keys
         *
         * @param request list queue request
         * @return ListKeysResponse
         * @throws Core::DatabaseException
         * @see Dto::KMS::ListKeysRequest
         * @see Dto::KMS::ListKeysResponse
         */
        Dto::KMS::ListKeysResponse ListKeys(const Dto::KMS::ListKeysRequest &request);

        /**
         * Creates a new key
         *
         * @param request create key request
         * @return CreateKeyResponse
         * @see Dto::KMS::CreateKeyRequest
         * @see Dto::KMS::CreateKeyResponse
         */
        Dto::KMS::CreateKeyResponse CreateKey(const Dto::KMS::CreateKeyRequest &request);

        /**
         * Schedules a key deletion
         *
         * @param request create queue request
         * @return ScheduleKeyDeletionRequest
         * @throws Core::DatabaseException
         * @see Dto::KMS::ScheduledKeyDeletionResponse
         */
        Dto::KMS::ScheduledKeyDeletionResponse ScheduleKeyDeletion(const Dto::KMS::ScheduleKeyDeletionRequest &request);

      private:

        /**
         * Account ID
         */
        std::string _accountId;

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Database connection
         */
        Database::KMSDatabase &_kmsDatabase;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_SERVICE_H
