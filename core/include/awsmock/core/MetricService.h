//
// Created by vogje01 on 07/01/2023.
//

#ifndef AWSMOCK_CORE_METRICSERVICE_H
#define AWSMOCK_CORE_METRICSERVICE_H

// C++ Standard includes
#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/resource.h>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Timer.h>
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include <Poco/Prometheus/Counter.h>
#include <Poco/Prometheus/Gauge.h>
#include <Poco/Prometheus/MetricsServer.h>
#include "Poco/Util/ServerApplication.h"

// AwsMock utils
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricSystemCollector.h>

#define TIME_DIFF(x) ((double) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _timerStartMap[GetTimerKey(x)]).count())

namespace AwsMock::Core {

    typedef std::map<std::string, Poco::Prometheus::Counter *> CounterMap;
    typedef std::map<std::string, Poco::Prometheus::Gauge *> GaugeMap;
    typedef std::map<std::string, Poco::Prometheus::Gauge *> TimerMap;
    typedef std::map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> TimerStartMap;

    /**
     * Maintains a list of counter and gauges for monitoring via Prometheus. The data is made available via a HTTP
     * server listening on port 8081. The port ist configurable.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class MetricService {

    public:

      /**
       * Default constructor
       */
      MetricService() : _logger(Poco::Logger::get("root")), _port(8081), _timeout(60000) {}

      /**
       * Constructor
       *
       * @param configuration application configuration
       */
      explicit MetricService(const Configuration &configuration);

      /**
       * Constructor.
       *
       * @param port prometheus serer port
       * @param timeout timout for the system collector
       */
      explicit MetricService(int port, long timeout);

      /**
       * Destructor
       */
      virtual ~MetricService();

      /**
       * Initialization
       */
      [[maybe_unused]] virtual void Initialize();

      /**
       * Gracefully shutdown
       */
      [[maybe_unused]]
      void ShutdownServer();

      /**
       * Starts the HTTP server
       */
      [[maybe_unused]]
      void StartServer();

      /**
       * Adds a counter to the map.
       *
       * @param name name of the counter
       */
      void AddCounter(const std::string &name);

      /**
       * Check whether a counter exists
       *
       * @param name name of the counter.
       * @return true if counter exists.
       */
      bool CounterExists(const std::string &name);

      /**
       * Increments a counter.
       *
       * @param name of the counter
       * @param value value for the incrementation (default: 1), can be negative
       */
      [[maybe_unused]]
      void IncrementCounter(const std::string &name, int value = 1);

      /**
       * Clears a counter.
       *
       * @param name of the counter
       */
      [[maybe_unused]]
      void ClearCounter(const std::string &name);

      /**
       * Adds a gauge to the map.
       *
       * @param name name of the gauge
       */
      void AddGauge(const std::string &name);

      /**
       * Adds a gauge to the map.
       *
       * @param name name of the gauge
       * @param label label of the gauge
       */
      void AddGauge(const std::string &name, const std::string &label);

      /**
       * Check whether a gauge exists
       *
       * @param name name of the gauge.
       * @return true if gauge exists.
       */
      bool GaugeExists(const std::string &name);

      /**
       * Check whether a gauge exists
       *
       * @param name name of the gauge.
       * @param label label of the gauge.
       * @return true if gauge exists.
       */
      bool GaugeExists(const std::string &name, const std::string &label);

      /**
       * Sets a integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, int value);

      /**
       * Sets a integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value);

      /**
       * Sets a long integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, long value);

      /**
       * Sets a long integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, long value);

      /**
       * Sets a unsigned long integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, unsigned long value);

      /**
       * Sets a unsigned long integer gauge value in the map.
       *
       * @param name name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, unsigned long value);

      /**
       * Sets a float gauge value in the map.
       *
       * @param name name of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, float value);

      /**
       * Sets a float gauge value in the map.
       *
       * @param name name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, float value);

      /**
       * Sets a double gauge value in the map.
       *
       * @param name name of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, double value);

      /**
       * Sets a double gauge value in the map.
       *
       * @param name name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value of the gauge
       */
      [[maybe_unused]]
      void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value);

      /**
       * Increments a gauge.
       *
       * @param name of the gauge
       * @param value value for the incrementation (default: 1), can be negative
       */
      [[maybe_unused]]
      void IncrementGauge(const std::string &name, int value = 1);

      /**
       * Increments a gauge.
       *
       * @param name of the gauge
       * @param labelName label name of the gauge
       * @param labelValue label value of the gauge
       * @param value value for the incrementation (default: 1), can be negative
       */
      [[maybe_unused]]
      void IncrementGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value = 1);

      /**
       * Add timer
       */
      void AddTimer(const std::string &name);

      /**
       * Starts a timer
       *
       * @param name name of the timer.
       */
      void StartTimer(const std::string &name);

      /**
       * Stop and fill in the duration of a timer
       *
       * @param name name of the timer.
       */
      void StopTimer(const std::string &name);

      /**
       * Resets a timers.
       *
       * @param name name of the timer.
       */
      [[maybe_unused]]
      void ResetTimer(const std::string &name);

      /**
       * Resets all timers.
       *
       * @param name name of the timer.
       */
      [[maybe_unused]]
      void ResetAllTimer();

      /**
       * Check whether a timer exists
       *
       * @param name name of the timer.
       * @return true if timer exists.
       */
      bool TimerExists(const std::string &name);

    private:

      /**
       * Returns a thread safe timer key string.
       *
       * @param name name of the timer.
       */
      std::string GetTimerKey(const std::string &name);

      /**
       * Initialize system counter
       */
      void StartSystemCounter();

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Metric server for Prometheus
       */
      Poco::Prometheus::MetricsServer *_server{};

      /**
       * System monitoring thread
       */
      MetricSystemCollector* _metricSystemCollector{};

      /**
       * System monitoring thread
       */
      Poco::Timer *_metricSystemTimer{};

      /**
       * Counter map
       */
      CounterMap _counterMap;

      /**
       * Counter map
       */
      GaugeMap _gaugeMap;

      /**
       * Timer map
       */
      TimerMap _timerMap;

      /**
       * Timer start map
       */
      TimerStartMap _timerStartMap;

      /**
       * Port for the monitoring server
       */
      long _port;

      /**
       * System collector timeout
       */
      long _timeout;

      /**
       * Mutex
       */
      Poco::Mutex _mutex;
    };

}// namespace AwsMock::Core

#endif  // AWSMOCK_CORE_METRICSERVICE_H
