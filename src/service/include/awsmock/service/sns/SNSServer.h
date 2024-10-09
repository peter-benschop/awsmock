//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SNS_SERVER_H
#define AWSMOCK_SERVICE_SNS_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sns/SNSMonitoring.h>
#include <awsmock/service/sns/SNSWorker.h>

#define SNS_DEFAULT_WORKER_PERIOD 300
#define SNS_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief SNS module server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit SNSServer(Core::PeriodicScheduler &scheduler);

      private:

        /**
         * @brief SNS monitoring
         */
        SNSMonitoring _snsMonitoring;

        /**
         * @brief SNS worker
         */
        SNSWorker _snsWorker;

        /**
         * @brief SNS server period
         *
         * <p>
         * Used for the background threads (cleanup, reset, retention, etc.)
         * </p>
         */
        int _workerPeriod;

        /**
         * @brief SNS monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SNSSERVER_H
