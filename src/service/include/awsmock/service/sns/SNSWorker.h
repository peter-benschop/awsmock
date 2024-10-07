//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SNS_WORKER_H
#define AWSMOCK_SERVICE_SNS_WORKER_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SNSDatabase.h>

#define SNS_DEFAULT_MESSAGE_TIMEOUT 14

namespace AwsMock::Service {

    /**
     * @brief SNS worker thread
     *
     * <p>
     * Used as background thread to do maintenance work, like resetting topics, deleted old message etc.
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSWorker {

      public:

        /**
         * @brief Constructor
         */
        explicit SNSWorker() = default;

        /**
         * @brief Delete resources, which are over the retention period.
         */
        void DeleteOldMessages();

      private:

        /**
         * @brief Database connection
         */
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SNS_WORKER_H
