//
// Created by vogje01 on 6/3/24.
//

#ifndef AWSMOCK_SERVICE_MODULE_MONITORING_H
#define AWSMOCK_SERVICE_MODULE_MONITORING_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/monitoring/MetricSystemCollector.h>
#include <awsmock/repository/ModuleDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief Manager monitoring
     *
     * Reports up/down status of modules using the following correlations:
     *
     *  - Active && running == 0
     *  - Active && not running == 2
     *  - Not Active && not running == 0
     *  - Not Active && running == 1
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleMonitoring : public Core::Timer {

      public:

        /**
         * @brief Constructor
         * @param timeout monitoring period
         */
        explicit ModuleMonitoring(int timeout);

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
         * Update the counter
         */
        void UpdateCounter();

        /**
         * Module database connection
         */
        Database::ModuleDatabase &_moduleDatabase = Database::ModuleDatabase::instance();
    };

}// namespace AwsMock::Service
#endif// AWSMOCK_SERVICE_MODULE_MONITORING_H
