//
// Created by vogje01 on 07/01/2023.
//

#include <awsmock/core/monitoring/MetricService.h>

namespace AwsMock::Core {

    boost::mutex MetricService::_mutex;

    MetricService::MetricService() : Core::Timer("MetricServer") {

        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.monitoring.port", 9091);
    }

    void MetricService::Initialize() {

        // create an http server running on port 8080
        _exposer = std::make_shared<prometheus::Exposer>("127.0.0.1:" + std::to_string(_port));

        // create a metrics registry
        // @note it's the users responsibility to keep the object alive
        _registry = std::make_shared<prometheus::Registry>();

        _metricSystemCollector = std::make_shared<MetricSystemCollector>();
        log_debug << "Prometheus manager initialized, port: " << _port;

        _exposer->RegisterCollectable(_registry);
        log_info << "Monitoring manager started, port: " << _port;
    }

    void MetricService::Run() {
    }

    void MetricService::Shutdown() {
        _metricSystemCollector->Stop();
        log_info << "Metric module has been shutdown";
    }

    void MetricService::AddCounter(const std::string &name) {
        //boost::mutex::scoped_lock lock(_mutex);
        if (!CounterExists(name)) {
            prometheus::Family<prometheus::Counter> &counter = prometheus::BuildCounter()
                                                                       .Name(name)
                                                                       .Help(name)
                                                                       .Register(*_registry);
            _counterMap.emplace(name, counter);
            log_trace << "Counter added, name: " << name;
            return;
        }
        log_error << "Counter exists already, name: " << name;
    }

    void MetricService::AddCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        //boost::mutex::scoped_lock lock(_mutex);

        if (!CounterExists(name, labelName, labelValue)) {
            prometheus::Family<prometheus::Counter> &counter = prometheus::BuildCounter()
                                                                       .Name(name)
                                                                       .Help(name)
                                                                       .Register(*_registry);
            counter.Add({{labelName, labelValue}});
            _counterMap.emplace(name, counter);
            log_trace << "Counter added, name: " << name;
            return;
        }
        log_error << "Counter exists already, name: " << name;
    }

    bool MetricService::CounterExists(const std::string &name) {
        return _counterMap.find(name) != _counterMap.end();
    }

    bool MetricService::CounterExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_counterMap.begin(), _counterMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, prometheus::Family<prometheus::Counter> &> obj) {
                   auto &counter = reinterpret_cast<prometheus::Family<prometheus::Counter> &>(obj.second);
                   return obj.first == name && counter.Has({{labelName, labelValue}});
               }) != _counterMap.end();
    }

    prometheus::Family<prometheus::Counter> &MetricService::GetCounter(const std::string &name) {
        auto it = _counterMap.find(name);
        if (it != _counterMap.end()) {
            return it->second;
        }
    }

    prometheus::Family<prometheus::Counter> &MetricService::GetCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        auto it = std::find_if(_counterMap.begin(), _counterMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, prometheus::Family<prometheus::Counter> &> obj) {
            auto &counter = reinterpret_cast<prometheus::Family<prometheus::Counter> &>(obj.second);
            return obj.first == name && counter.Has({{labelName, labelValue}});
        });
        if (it != _counterMap.end()) {
            return it->second;
        }
    }

    void MetricService::ClearCounter(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (CounterExists(name)) {
            auto &counter = reinterpret_cast<prometheus::Counter &>(GetCounter(name));
            counter.Reset();
            log_trace << "Counter cleared, name: " << name;
            return;
        }
        log_error << "Counter not found, name: " << name;
    }

    void MetricService::ClearCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        boost::mutex::scoped_lock lock(_mutex);
        if (CounterExists(name, labelName, labelValue)) {
            auto &counter = reinterpret_cast<prometheus::Counter &>(GetCounter(name, labelName, labelValue));
            counter.Reset();
            log_trace << "Counter cleared, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
            return;
        }
        log_error << "Counter not found, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
    }

    void MetricService::IncrementCounter(const std::string &name, int value) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!CounterExists(name)) {
            AddCounter(name);
        }

        auto &counter = reinterpret_cast<prometheus::Counter &>(GetCounter(name));
        counter.Increment(value);
        log_trace << "Counter incremented, name: " << name;
    }

    void MetricService::IncrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!CounterExists(name, labelName, labelValue)) {
            AddCounter(name, labelName, labelValue);
        }
        auto &counter = reinterpret_cast<prometheus::Family<prometheus::Counter> &>(GetCounter(name, labelName, labelValue));
        counter.Add({{labelName, labelValue}}).Increment(value);
        log_trace << "Counter incremented, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
    }

    void MetricService::AddGauge(const std::string &name) {
        /*   boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;*/
    }

    void MetricService::AddGauge(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        /*  boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name, {.labelNames{label}});
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;*/
    }

    void MetricService::SetGauge(const std::string &name, double value) {
        /*boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set(value);
        log_trace << "Gauge value set, name: " << name;*/
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value) {
        /* boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name);
        }
        _gaugeMap[name]->labels({labelValue}).set(value);
        log_trace << "Gauge value set, name: " << name;*/
    }

    bool MetricService::GaugeExists(const std::string &name) {
        return _gaugeMap.find(name) != _gaugeMap.end();
    }

    bool MetricService::GaugeExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_gaugeMap.begin(), _gaugeMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, prometheus::Family<prometheus::Gauge> &> obj) {
                   auto &gauge = reinterpret_cast<prometheus::Family<prometheus::Gauge> &>(obj.second);
                   return obj.first == name && gauge.Has({{labelName, labelValue}});
               }) != _gaugeMap.end();
    }

    void MetricService::AddHistogram(const std::string &name) {
        /*boost::mutex::scoped_lock lock(_mutex);
        if (!HistogramExists(name)) {
            _histogramMap[name] = new Poco::Prometheus::Histogram(name);
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;*/
    }

    void MetricService::AddHistogram(const std::string &name, const std::string &label) {
        /* boost::mutex::scoped_lock lock(_mutex);
        if (!HistogramExists(name)) {
            _histogramMap[name] = new Poco::Prometheus::Histogram(name, {.labelNames{label}});
            log_trace << "Histogram added, name: " << name;
            return;
        }
        log_error << "Histogram exists already, name: " << name;*/
    }

    bool MetricService::HistogramExists(const std::string &name) {
        //return _histogramMap.find(name) != _histogramMap.end();
    }

    bool MetricService::HistogramExists(const std::string &name, const std::string &label) {
        /*auto it = _histogramMap.find(name);
        return it != _histogramMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();*/
    }

    void MetricService::AddTimer(const std::string &name) {
        //boost::mutex::scoped_lock lock(_mutex);
        if (!TimerExists(name)) {
            prometheus::Family<prometheus::Gauge> &timer = prometheus::BuildGauge()
                                                                   .Name(name)
                                                                   .Help(name)
                                                                   .Register(*_registry);
            _timerMap.emplace(name, timer);
            log_trace << "Timer added, name: " << name;
            return;
        }
        log_error << "Timer exists already, name: " << name;
    }

    void MetricService::AddTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        //boost::mutex::scoped_lock lock(_mutex);
        if (!TimerExists(name, labelName, labelValue)) {
            prometheus::Family<prometheus::Gauge> &timer = prometheus::BuildGauge()
                                                                   .Name(name)
                                                                   .Help(name)
                                                                   .Register(*_registry);
            timer.Add({{labelName, labelValue}});
            _timerMap.emplace(name, timer);
            log_trace << "Timer added, name: " << name;
            return;
        }
        log_error << "Timer exists already, name: " << name;
    }

    prometheus::Family<prometheus::Gauge> &MetricService::GetTimer(const std::string &name) {
        auto it = _timerMap.find(name);
        if (it != _timerMap.end()) {
            return it->second;
        }
    }

    prometheus::Family<prometheus::Gauge> &MetricService::GetTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        auto it = std::find_if(_timerMap.begin(), _timerMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, prometheus::Family<prometheus::Gauge> &> obj) {
            auto &gauge = reinterpret_cast<prometheus::Family<prometheus::Gauge> &>(obj.second);
            return obj.first == name && gauge.Has({{labelName, labelValue}});
        });
        if (it != _timerMap.end()) {
            return it->second;
        }
    }

    void MetricService::StartTimer(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!TimerExists(name)) {
            AddTimer(name);
        }
        if (_timerStartMap.find(GetTimerStartKey(name)) == _timerStartMap.end()) {
            _timerStartMap[GetTimerStartKey(name)] = std::chrono::high_resolution_clock::now();
            log_trace << "Timer started, name: " << name;
        }
    }

    void MetricService::StartTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!TimerExists(name, labelName, labelValue)) {
            AddTimer(name, labelName, labelValue);
        }
        if (_timerStartMap.find(GetTimerStartKey(name, labelName, labelValue)) == _timerStartMap.end()) {
            _timerStartMap[GetTimerStartKey(name, labelName, labelValue)] = std::chrono::high_resolution_clock::now();
            log_trace << "Timer started, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
        }
    }

    void MetricService::StopTimer(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (TimerExists(name)) {

            auto &timer = reinterpret_cast<prometheus::Gauge &>(GetTimer(name));
            timer.Set(TIME_DIFF_NAME(name));

            const auto count = std::erase_if(_timerStartMap, [name](const auto &item) {
                return item.first == GetTimerStartKey(name);
            });
            log_trace << "Timer stopped, name: " << name << " count: " << count << " size: " << _timerStartMap.size();
        }
    }

    void MetricService::StopTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        boost::mutex::scoped_lock lock(_mutex);
        if (TimerExists(name, labelName, labelValue)) {

            auto &timer = reinterpret_cast<prometheus::Gauge &>(GetTimer(name, labelName, labelValue));
            timer.Set(TIME_DIFF_LABEL(name, labelName, labelValue));

            std::erase_if(_timerStartMap, [name, labelName, labelValue](const auto &item) {
                auto const &[key, value] = item;
                return key == GetTimerStartKey(name, labelName, labelValue);
            });

            log_trace << "Timer stopped, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue << " size: " << _timerStartMap.size();
        }
    }

    bool MetricService::TimerExists(const std::string &name) {
        return _timerMap.find(name) != _timerMap.end();
    }

    bool MetricService::TimerExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_timerMap.begin(), _timerMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, prometheus::Family<prometheus::Gauge> &> obj) {
                   auto &gauge = reinterpret_cast<prometheus::Family<prometheus::Gauge> &>(obj.second);
                   return obj.first == name && gauge.Has({{labelName, labelValue}});
               }) != _timerMap.end();
    }

    void MetricService::ResetTimer(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (TimerExists(name)) {
            auto &timer = reinterpret_cast<prometheus::Gauge &>(GetTimer(name));
            timer.Set(0);
        }
        log_trace << "Timer cleared, name: " << name;
    }

    void MetricService::ResetAllTimer() {
        boost::mutex::scoped_lock lock(_mutex);
        for (const auto &t: _timerMap) {
            auto &timer = reinterpret_cast<prometheus::Gauge &>(GetTimer(t.first));
            timer.Set(0);
        }
    }

    std::string MetricService::GetTimerKey(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return name + "::" + labelName + "::" + labelValue;
    }

    std::string MetricService::GetTimerStartKey(const std::string &name) {
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        log_trace << "Timer key returned, name: " << name;
        return name + "::" + std::to_string(threadID);
    }

    std::string MetricService::GetTimerStartKey(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        log_trace << "Timer key returned, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
        return name + "::" + labelName + "::" + labelValue + "::" + std::to_string(threadID);
    }

}// namespace AwsMock::Core