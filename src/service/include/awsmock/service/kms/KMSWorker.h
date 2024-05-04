//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_KMS_WORKER_H
#define AWSMOCK_SERVICE_KMS_WORKER_H

// AwsMock includes
#include "awsmock/dto/kms/model/KeyState.h"
#include <awsmock/core/Timer.h>
#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Service {

    /**
     * KMS worker thread
     *
     * <p>
     * Used as background thread to do maintenance work.
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSWorker : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit KMSWorker(int timeout) : Core::Timer("kms-worker", timeout) {}

        /**
         * Initialization
         */
        void Initialize() override;

        /**
         * Main method
         */
        void Run() override;

        /**
         * Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Delete keys which are pending for deletion
         */
        void DeleteKeys();

        /**
         * Database connection
         */
        Database::KMSDatabase &_kmsDatabase = Database::KMSDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_WORKER_H
