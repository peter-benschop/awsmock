//
// Created by vogje01 on 01/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H
#define AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H

// C++ Standard includes
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include <sys/times.h>

// Poco includes
#include <Poco/Timer.h>
#include <Poco/Prometheus/Counter.h>
#include <Poco/Prometheus/Gauge.h>
#include <Poco/Prometheus/MetricsServer.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Timer.h>

// System counter
#define VIRTUAL_MEMORY "virtual_memory_used"
#define REAL_MEMORY "real_memory_used"
#define TOTAL_THREADS "total_threads"
#define TOTAL_CPU "total_cpu"
#define USER_CPU "user_cpu"
#define SYSTEM_CPU "system_cpu"

namespace AwsMock::Core {

  /**
   * Collect system information like CPU and Memory. Runs as background thread with a given timeout in ms.
   *
   * @author jens.vogt@opitz-consulting.com
  */
  class MetricSystemCollector : public Core::Timer {

  public:

    /**
     * Constructor.
     */
    explicit MetricSystemCollector();

    /**
     * Destructor.
     */
    ~MetricSystemCollector();

    /**
     * Initialization
     */
    void Initialize() override;

    /**
     * Runnable method
     */
    void Run() override;

    /**
     * Shutdown
     */
    void Shutdown() override;

  private:

    /**
     * Updates the system counter
     */
    void CollectSystemCounter();

    /**
     * Virtual memory gauge
     */
    Poco::Prometheus::Gauge *_virtualMemory;

    /**
     * Real memory gauge
     */
    Poco::Prometheus::Gauge *_realMemory;

    /**
     * Total thread gauge
     */
    Poco::Prometheus::Gauge *_totalThreads;

    /**
     * Total CPU gauge
     */
    Poco::Prometheus::Gauge *_totalCpu;

    /**
     * User CPU gauge
     */
    Poco::Prometheus::Gauge *_userCpu;

    /**
     * System CPU gauge
     */
    Poco::Prometheus::Gauge *_systemCpu;

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

  };
} // namespace AwsMock::Core

#endif //AWSMOCK_CORE_METRIC_SYSTEM_COLLECTOR_H
