//
// Created by vogje01 on 18/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
#define AWSMOCK_CORE_METRIC_SERVICE_TIMER_H

#include "MetricService.h"

#include <utility>

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
         * Constructor
         *
         * <p>Measure a methods execution time.</p>
         *
         * @param metricService metric module
         * @param name name of the underlying timer
         *
         * @author jens.vogt\@opitz-consulting.com
         */
        explicit MetricServiceTimer(std::string name) : _metricService(MetricService::instance()), _name(std::move(name)) {
            if (!_metricService.TimerExists(_name)) {
                _metricService.AddTimer(_name);
            }
            _metricService.StartTimer(_name);
        }

        /**
         * Constructor
         *
         * <p>Measure a methods execution time.</p>
         *
         * @param metricService metric module
         * @param name name of the underlying timer
         *
         * @author jens.vogt\@opitz-consulting.com
         */
        explicit MetricServiceTimer(std::string name, std::string label) : _metricService(MetricService::instance()), _name(std::move(name)), _label(std::move(label)) {
            if (!_metricService.TimerExists(_name, _label)) {
                _metricService.AddTimer(_name, _label);
            }
            _metricService.StartTimer(_name, _label);
        }

        /**
         * Destructor
         */
        ~MetricServiceTimer() {
            if (_label.empty()) {
                _metricService.StopTimer(_name);
            } else {
                _metricService.StopTimer(_name, _label);
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
         * Label of the timer
         */
        const std::string _label{};
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
