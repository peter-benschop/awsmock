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
     * SQS worker thread
     *
     * <p>
     * Used as background thread to do maintenance work, like resetting messages, deleted old message etc.
     * </p>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class SQSWorker : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit SQSWorker(int timeout) : Core::Timer("sns-worker", timeout) {}

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
         * Reset messages
         *
         * <p>Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.</p>
         * <p>Checks also the expiration date and removed the messages, which are older than the max retention period.</>
         */
        [[maybe_unused]] void ResetMessages();

        /**
         * Database connection
         */
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();

    };
}
#endif // AWSMOCK_SERVICE_SQS_WORKER_H
