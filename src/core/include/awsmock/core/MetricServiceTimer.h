//
// Created by vogje01 on 18/05/2023.
//

#ifndef AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
#define AWSMOCK_CORE_METRIC_SERVICE_TIMER_H

#include <awsmock/core/MetricService.h>

#include <utility>

namespace AwsMock::Core {

  template<class M>
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
       * @author jens.vogt@opitz-consulting.com
       */
      explicit MetricServiceTimer(M &metricService, std::string name)
          : _metricService(metricService), _name(std::move(name)) {
        if (!_metricService.TimerExists(_name)) {
          _metricService.AddTimer(_name);
        }
        _metricService.StartTimer(_name);
      }

      /**
       * Destructor
       */
      ~MetricServiceTimer() {
        _metricService.StopTimer(_name);
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
      M &_metricService;

      /**
       * Name of the timer
       */
      const std::string _name;
  };

} // namespace AwsMock::Core

#endif //AWSMOCK_CORE_METRIC_SERVICE_TIMER_H
