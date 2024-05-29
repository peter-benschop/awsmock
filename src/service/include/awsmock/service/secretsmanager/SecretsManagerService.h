//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_SERVICE_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_SERVICE_H

// C++ standard includes
#include <chrono>
#include <ctime>
#include <map>
#include <string>
#include <thread>

// AwsMock includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/dto/secretsmanager/CreateSecretRequest.h>
#include <awsmock/dto/secretsmanager/CreateSecretResponse.h>
#include <awsmock/dto/secretsmanager/DeleteSecretRequest.h>
#include <awsmock/dto/secretsmanager/DeleteSecretResponse.h>
#include <awsmock/dto/secretsmanager/DescribeSecretRequest.h>
#include <awsmock/dto/secretsmanager/DescribeSecretResponse.h>
#include <awsmock/dto/secretsmanager/GetSecretValueRequest.h>
#include <awsmock/dto/secretsmanager/GetSecretValueResponse.h>
#include <awsmock/dto/secretsmanager/ListSecretsRequest.h>
#include <awsmock/dto/secretsmanager/ListSecretsResponse.h>
#include <awsmock/dto/secretsmanager/RotateSecretRequest.h>
#include <awsmock/dto/secretsmanager/RotateSecretResponse.h>
#include <awsmock/dto/secretsmanager/UpdateSecretRequest.h>
#include <awsmock/dto/secretsmanager/UpdateSecretResponse.h>
#include <awsmock/repository/SecretsManagerDatabase.h>

#define DEFAULT_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    /**
     * @brief Secrets manager service.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SecretsManagerService {

      public:

        /**
         * Constructor
         *
         * @param configuration module configuration
         */
        explicit SecretsManagerService(Core::Configuration &configuration);

        /**
         * Create a new secret
         *
         * @param request create secret request
         * @return CreateSecretResponse
         */
        Dto::SecretsManager::CreateSecretResponse CreateSecret(const Dto::SecretsManager::CreateSecretRequest &request);

        /**
         * Describes an existing secret
         *
         * @param request describe secret request
         * @return DescribeSecretResponse
         */
        Dto::SecretsManager::DescribeSecretResponse DescribeSecret(const Dto::SecretsManager::DescribeSecretRequest &request);

        /**
         * Returns the secret value
         *
         * @param request get secret value request
         * @return GetSecretValueResponse
         */
        Dto::SecretsManager::GetSecretValueResponse GetSecretValue(const Dto::SecretsManager::GetSecretValueRequest &request);

        /**
         * List existing secrets
         *
         * @param request list secrets request
         * @return ListSecretsResponse
         */
        Dto::SecretsManager::ListSecretsResponse ListSecrets(const Dto::SecretsManager::ListSecretsRequest &request);

        /**
         * Updates an existing secret
         *
         * @param request update secret request
         * @return UpdateSecretResponse
         */
        Dto::SecretsManager::UpdateSecretResponse UpdateSecret(const Dto::SecretsManager::UpdateSecretRequest &request);

        /**
         * Rotates an existing secret
         *
         * @param request rotate secret request
         * @return RotateSecretResponse
         */
        Dto::SecretsManager::RotateSecretResponse RotateSecret(const Dto::SecretsManager::RotateSecretRequest &request);

        /**
         * Deletes an existing secret
         *
         * @param request delete secret request
         * @return DeleteSecretResponse
         */
        Dto::SecretsManager::DeleteSecretResponse DeleteSecret(const Dto::SecretsManager::DeleteSecretRequest &request);

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
        Database::SecretsManagerDatabase &_database;

        /**
         * Shutdown mutex
         */
        Poco::Mutex _mutex;

        /**
         * Key management system key
         */
        std::string _kmsKey;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SECRETSMANAGER_SERVICE_H
