//
// Created by vogje01 on 07/01/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SERVICE_H
#define AWSMOCK_CORE_METRIC_SERVICE_H

// C includes
// C++ Standard includes
#include <chrono>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Prometheus/Counter.h>
#include <Poco/Prometheus/Gauge.h>
#include <Poco/Prometheus/Histogram.h>
#include <Poco/Prometheus/MetricsServer.h>

// Boost include
#include <boost/thread/mutex.hpp>

// AwsMock utils
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Timer.h>

namespace AwsMock::Core {

    using std::chrono::high_resolution_clock;
    using std::chrono::time_point;

    typedef std::map<std::string, Poco::Prometheus::Counter *> CounterMap;
    typedef std::map<std::string, Poco::Prometheus::Gauge *> GaugeMap;
    typedef std::map<std::string, Poco::Prometheus::Histogram *> HistogramMap;

    /**
     * @brief Monitoring server
     *
     * Maintains a list of counter and gauges for monitoring via Prometheus. The data is made available via a HTTP
     * manager listening on port 9100. The port ist configurable.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MetricService : public Core::Timer {

      public:

        /**
         * @brief Default constructor
         */
        MetricService();

        /**
         * @brief Singleton instance
         */
        static MetricService &instance() {
            static MetricService metricService;
            return metricService;
        }

        /**
         * @brief Destructor
         */
        virtual ~MetricService() = default;

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Run main loop
         */
        void Run() override;

        /**
         * @brief Gracefully shutdown
         */
        void Shutdown() override;

        /**
         * @brief Increments a counter.
         *
         * @param name of the counter
         * @param value value for the incrementation (default: 1), can be negative
         */
        void IncrementCounter(const std::string &name, int value = 1);

        /**
         * @brief Increments a labeled counter.
         *
         * @param name of the counter
         * @param labelName name of the label
         * @param labelValue label value of the counter
         * @param value value for the incrementation (default: 1), can be negative
         */
        void IncrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value = 1);

        /**
         * @brief Clears a counter.
         *
         * @param name of the counter
         */
        void ClearCounter(const std::string &name);

        /**
         * @brief Clears a counter.
         *
         * @param name of the counter
         * @param labelName name of the label
         * @param labelValue label value of the counter
         */
        void ClearCounter(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Sets a double gauge value in the map.
         *
         * @param name name of the gauge
         * @param value value of the gauge
         */
        [[maybe_unused]] void SetGauge(const std::string &name, double value);

        /**
         * @brief Sets a double gauge value in the map.
         *
         * @param name name of the gauge
         * @param labelName label name of the gauge
         * @param labelValue label value of the gauge
         * @param value value of the gauge
         */
        void SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value);

      private:

        /**
         * @brief Adds a counter to the map.
         *
         * @param name name of the counter
         */
        void AddCounter(const std::string &name);

        /**
         * @brief Adds a counter to the map.
         *
         * @param name name of the counter
         * @param labelName label name of the counter
         * @param labelValue label value of the counter
         */
        void AddCounter(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Check whether a counter exists
         *
         * @param name name of the counter.
         * @return true if counter exists.
         */
        bool CounterExists(const std::string &name);

        /**
         * @brief Check whether a counter exists
         *
         * @param name name of the counter.
         * @param labelName label name of the counter
         * @param labelValue label value of the counter
         * @return true if counter exists.
         */
        bool CounterExists(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Get a specific metric
         *
         * @param name name of the metric
         * @return metric if existing.
         */
        Poco::Prometheus::Counter *GetCounter(const std::string &name);

        /**
         * @brief Get a specific metric by name, labelName and labelValue
         *
         * @param name name of the metric
         * @param labelName name of the metric label
         * @param labelValue value of the metric label
         * @return metric if existing.
         */
        Poco::Prometheus::Counter *GetCounter(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Returns a timer key string.
         *
         * @param name name of the timer.
         * @param labelName label name of the timer.
         * @param labelValue label value of the timer.
         */
        static std::string GetTimerKey(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Returns a thread safe timer key string.
         *
         * @param name name of the timer.
         */
        static std::string GetTimerStartKey(const std::string &name);

        /**
         * @brief Returns a thread safe timer key string.
         *
         * @param name name of the timer.
         * @param labelName label name of the timer.
         * @param labelValue label value of the timer.
         */
        static std::string GetTimerStartKey(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Adds a gauge to the map.
         *
         * @param name name of the gauge
         */
        void AddGauge(const std::string &name);

        /**
         * @brief Adds a gauge to the map.
         *
         * @param name name of the gauge
         * @param labelName name of the label
         * @param labelValue label value of the counter
         */
        void AddGauge(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Check whether a gauge exists
         *
         * @param name name of the gauge.
         * @return true if gauge exists.
         */
        bool GaugeExists(const std::string &name);

        /**
         * @brief Check whether a gauge exists
         *
         * @param name name of the gauge.
         * @param labelName name of the label
         * @param labelValue label value of the counter
         * @return true if gauge exists.
         */
        bool GaugeExists(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * @brief Get a specific metric
         *
         * @param name name of the metric
         * @return metric if existing.
         */
        Poco::Prometheus::Gauge *GetGauge(const std::string &name);

        /**
         * @brief Get a specific metric by name, labelName and labelValue
         *
         * @param name name of the metric
         * @param labelName name of the metric label
         * @param labelValue value of the metric label
         * @return metric if existing.
         */
        Poco::Prometheus::Gauge *GetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue);

        /**
         * Metric manager for Prometheus
         */
        std::shared_ptr<Poco::Prometheus::MetricsServer> _server;

        /**
         * Counter map
         */
        CounterMap _counterMap;

        /**
         * Counter map
         */
        GaugeMap _gaugeMap;

        /**
         * Counter map
         */
        HistogramMap _histogramMap;

        /**
         * Port for the monitoring manager
         */
        long _port;

        /**
         * Mutex
         */
        static boost::mutex _mutex;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_METRIC_SERVICE_H
