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
#include <awsmock/repository/KMSDatabase.h>

#define DEFAULT_KMS_ACCOUNT_ID "000000000000"

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
         * Creates a new queue
         *
         * <p>In case the topic exists already, return the existing topic.</p>
         *
         * @param request create queue request
         * @return CreateQueueResponse
         */
        Dto::KMS::CreateKeyResponse CreateKey(const Dto::KMS::CreateKeyRequest &request);

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
