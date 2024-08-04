//
// Created by vogje01 on 18/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
#define AWSMOCK_CORE_METRIC_SERVICE_TIMER_H

#include <awsmock/core/monitoring/MetricService.h>

#define TIME_DIFF_NAME(x) (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - _start).count())
#define TIME_DIFF_LABEL(x, y, z) (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - _start).count())

namespace AwsMock::Core {

    using std::chrono::high_resolution_clock;
    using std::chrono::time_point;

    /**
     * @brief Measures the execution time of a method.
     *
     * Is self-destroying, which means the timer is automatically destroyed, when the method goes out of scope.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MetricServiceTimer {

      public:

        /**
         * @brief Constructor
         *
         * <p>Measure a methods execution time.</p>
         *
         * @param name name of the underlying timer
         */
        explicit MetricServiceTimer(std::string name) : _metricService(MetricService::instance()), _name(std::move(name)), _start(high_resolution_clock::now()) {}

        /**
         * @brief Constructor
         *
         * <p>Measure a methods execution time.</p>
         *
         * @param name name of the underlying timer
         * @param labelName label name of the underlying timer
         * @param labelValue label value of the underlying timer
         */
        explicit MetricServiceTimer(std::string name, std::string labelName, std::string labelValue) : _metricService(MetricService::instance()), _name(std::move(name)),
                                                                                                       _labelName(std::move(labelName)), _labelValue(std::move(labelValue)),
                                                                                                       _start(high_resolution_clock::now()) {}

        /**
         * @brief Destructor
         *
         * Stop the timer and reports the execution to the metric service.
         */
        ~MetricServiceTimer() {
            if (_labelName.empty()) {
                _metricService.SetGauge(_name, TIME_DIFF_NAME(_name));
                log_trace << "Timer deleted, name: " << _name;
            } else {
                _metricService.SetGauge(_name, _labelName, _labelValue, TIME_DIFF_LABEL(_name, labelName, labelValue));
                log_trace << "Timer deleted, name: " << _name << " labelName: " << _labelName << " labelValue: " << _labelValue;
            }
        }

        /**
         * Default constructor
         */
        MetricServiceTimer() = delete;

        /**
         * Copy constructor
         */
        MetricServiceTimer(const MetricServiceTimer &) = delete;

        /**
         * Equals operator
         */
        MetricServiceTimer &operator=(const MetricServiceTimer &) = delete;

      private:

        /**
         * Metric module
         */
        MetricService &_metricService;

        /**
         * Name of the timer
         */
        const std::string _name{};

        /**
         * Label name of the timer
         */
        const std::string _labelName{};

        /**
         * Label value of the timer
         */
        const std::string _labelValue{};

        /**
         * Timer start time point
         */
        time_point<high_resolution_clock> _start;
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
