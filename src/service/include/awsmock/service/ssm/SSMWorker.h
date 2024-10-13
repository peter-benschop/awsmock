//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SSM_WORKER_H
#define AWSMOCK_SERVICE_SSM_WORKER_H

// C++ includes
#include <chrono>
#include <string>

// AwsMock includes
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
    class SSMWorker {

      public:

        /**
         * @brief Constructor
         */
        explicit SSMWorker() = default;

        /**
         * @brief Delete keys which are pending for deletion
         */
        void DeleteKeys();

      private:

        /**
         * Database connection
         */
        Database::SSMDatabase &_kmsDatabase = Database::SSMDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_WORKER_H
