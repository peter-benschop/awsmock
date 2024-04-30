//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_CREATOR_H
#define AWSMOCK_SERVICE_KMS_CREATOR_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/dto/kms/KeySpec.h>
#include <awsmock/dto/kms/KeyState.h>
#include <awsmock/entity/kms/Key.h>
#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Service {

    /**
     * KMS async key creator
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSCreator {

      public:


        /**
         * Constructor
         */
        [[maybe_unused]] explicit KMSCreator() = default;

        /**
         * Create new KMS key
         *
         * @param keyId ID of the key
         */
        static void CreateKmsKey(const std::string &keyId);

      private:

        /**
         * Generate AES 256 key
         *
         * @param key key entity
         */
        [[maybe_unused]] static void GenerateAes256Key(Database::Entity::KMS::Key &key);

        /**
         * Generate a public/private key pair
         *
         * @param key key
         * @param length length
         * @see AwsMock::Core::CryptoUtils
         */
        [[maybe_unused]] static void GenerateRsaKeyPair(Database::Entity::KMS::Key &key, int length);
    };

}//namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_CREATOR_H
