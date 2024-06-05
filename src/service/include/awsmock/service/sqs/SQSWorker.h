//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SQS_WORKER_H
#define AWSMOCK_SERVICE_SQS_WORKER_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SQSDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief SQS worker thread
     *
     * Used as background thread to do maintenance work, like resetting resources, deleted old message etc.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSWorker : public Core::Timer {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSWorker(int timeout) : Core::Timer("sqs-worker", timeout) {}

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * @brief Reset resources
         *
         * @par
         * Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.
         *
         * @par
         * Checks also the expiration date and removed the resources, which are older than the max retention period.
         */
        [[maybe_unused]] void ResetMessages();

        /**
         * Database connection
         */
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_WORKER_H
