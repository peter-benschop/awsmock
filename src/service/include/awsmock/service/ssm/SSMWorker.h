//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SSM_WORKER_H
#define AWSMOCK_SERVICE_SSM_WORKER_H

// C++ includes
#include <chrono>
#include <string>

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SSMDatabase.h>

namespace AwsMock::Service {

    using std::chrono::system_clock;

    /**
     * @brief SSM worker thread
     *
     * @par
     * Used as background thread to do maintenance work. The SSM monitoring is 'self-starting', which means the constructor start
     * itself as a background process.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMWorker : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit SSMWorker(int timeout);

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
        Database::SSMDatabase &_kmsDatabase = Database::SSMDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_WORKER_H
