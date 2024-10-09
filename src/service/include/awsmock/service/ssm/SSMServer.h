//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SSM_SERVER_H
#define AWSMOCK_SERVICE_SSM_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/ssm/SSMMonitoring.h>
#include <awsmock/service/ssm/SSMWorker.h>

#define SSM_DEFAULT_WORKER_PERIOD 3600
#define SSM_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief SSM module server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit SSMServer(Core::PeriodicScheduler &scheduler);

      private:

        /**
         * SSM monitoring
         */
        SSMMonitoring _ssmMonitoring;

        /**
         * SSM worker
         */
        SSMWorker _ssmWorker;

        /**
         * SSM server period
         *
         * <p>
         * Used for the background threads (cleanup, reset, retention, etc.)
         * </p>
         */
        int _workerPeriod;

        /**
         * SNS monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_SERVER_H
