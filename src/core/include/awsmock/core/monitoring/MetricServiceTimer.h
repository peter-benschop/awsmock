//
// Created by vogje01 on 18/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
#define AWSMOCK_CORE_METRIC_SERVICE_TIMER_H

#include <awsmock/core/monitoring/MetricService.h>

namespace AwsMock::Core {

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
        explicit MetricServiceTimer(std::string name) : _metricService(MetricService::instance()), _name(std::move(name)) {
            _metricService.StartTimer(_name);
        }

        /**
         * @brief Constructor
         *
         * <p>Measure a methods execution time.</p>
         *
         * @param name name of the underlying timer
         * @param label label of the underlying timer
         */
        explicit MetricServiceTimer(std::string name, std::string labelName, std::string labelValue) : _metricService(MetricService::instance()), _name(std::move(name)), _labelName(std::move(labelName)), _labelValue(std::move(labelValue)) {
            _metricService.StartTimer(_name, _labelName, _labelValue);
        }

        /**
         * Destructor
         */
        ~MetricServiceTimer() {
            if (_labelName.empty()) {
                _metricService.StopTimer(_name);
            } else {
                _metricService.StopTimer(_name, _labelName, _labelValue);
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
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
