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
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/entity/kms/Key.h>
#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Service {

    /**
     * KMS async key creator
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSCreator {

      public:

        /**
         * Constructor
         */
        [[maybe_unused]] explicit KMSCreator() : _kmsDatabase(Database::KMSDatabase::instance()) {}

        /**
         * Create new KMS key
         *
         * @param keyId ID of the key
         */
        void CreateKmsKey(const char *keyId);

      private:

        void GenerateKey();

        /**
         * Database connection
         */
        Database::KMSDatabase &_kmsDatabase;
    };

}//namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_CREATOR_H
