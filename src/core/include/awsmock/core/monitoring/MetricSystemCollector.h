//
// Created by vogje01 on 01/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H
#define AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H

// C includes
#include <sys/times.h>

// C++ Standard includes
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/Timer.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricService.h>

// System counter

namespace AwsMock::Core {

    /**
     * @brief Collect system information like CPU and Memory.
     *
     * Runs as background thread with a given timeout in ms.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MetricSystemCollector : public Core::Timer {

      public:

        /**
         * @brief Constructor.
         */
        explicit MetricSystemCollector() : Core::Timer("SystemCollector") {}

        /**
         * @brief Singleton instance
         */
        static MetricSystemCollector &instance() {
            static MetricSystemCollector metricSystemCollector;
            return metricSystemCollector;
        }

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Runnable method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * @brief Updates the system counter
         */
        void CollectSystemCounter();

        /**
         * Number of processors
         */
        int numProcessors{};

        /**
         * Last CPU
         */
        clock_t lastCPU{};

        /**
         * Last system CPU
         */
        clock_t lastSysCPU{};

        /**
         * Last user CPU
         */
        clock_t lastUserCPU{};

        /**
         * Monitoring period
         */
        int _period = 60;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H
