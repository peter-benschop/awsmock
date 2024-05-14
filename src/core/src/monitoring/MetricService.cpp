//
// Created by vogje01 on 07/01/2023.
//

#include <awsmock/core/MetricService.h>

namespace AwsMock::Core {

    Poco::Mutex MetricService::_mutex;

    MetricService::MetricService() : Core::Timer("MetricServer") {

        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.monitoring.port", 9100);
    }

    void MetricService::Initialize() {
        _server = std::make_shared<Poco::Prometheus::MetricsServer>(static_cast<Poco::UInt16>(_port));
        _metricSystemCollector = std::make_shared<MetricSystemCollector>();
        log_debug << "Prometheus manager initialized, port: " << _port;

        if (_server != nullptr) {
            _server->start();
        }
        log_info << "Monitoring manager started, port: " << _port;
    }

    void MetricService::Run() {
    }

    void MetricService::Shutdown() {
        _server->stop();
        _metricSystemCollector->Stop();
        log_info << "Metric module has been shutdown";
    }

    void MetricService::AddCounter(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name)) {
            _counterMap[name] = new Poco::Prometheus::Counter(name);
            _counterMap[name]->clear();
            log_trace << "Counter added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    void MetricService::AddCounter(const std::string &name, const std::string &label) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name, label)) {
            _counterMap[name] = new Poco::Prometheus::Counter(name, {.labelNames{label}});
            log_trace << "Counter added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    bool MetricService::CounterExists(const std::string &name) {
        return std::find_if(_counterMap.begin(),
                            _counterMap.end(),
                            [name](const std::pair<std::string, Poco::Prometheus::Counter *> &timer) {
                                return timer.first == name;
                            }) != _counterMap.end();
    }

    bool MetricService::CounterExists(const std::string &name, const std::string &label) {
        auto it = _counterMap.find(name);
        return it != _counterMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();
    }

    void MetricService::ClearCounter(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (CounterExists(name)) {
            _counterMap[name]->clear();
            log_trace << "Counter cleared, name: " << name;
            return;
        }
        log_error << "Counter not found, name: " << name;
    }

    void MetricService::IncrementCounter(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name)) {
            AddCounter(name);
        }
        _counterMap[name]->inc((double) value);
        log_trace << "Counter incremented, name: " << name;
    }

    void MetricService::IncrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name, labelName)) {
            AddCounter(name, labelName);
        }
        _counterMap[name]->labels({labelValue}).inc((double) value);
        log_trace << "Counter incremented, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
    }

    void MetricService::DecrementCounter(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name)) {
            AddCounter(name);
        }
        _counterMap[name]->inc((double) -value);
        log_trace << "Counter incremented, name: " << name;
    }

    void MetricService::DecrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name, labelName)) {
            AddCounter(name, labelName);
        }
        _counterMap[name]->labels({labelValue}).inc((double) -value);
        log_trace << "Counter incremented, name: " << name;
    }

    void MetricService::AddGauge(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    void MetricService::AddGauge(const std::string &name, const std::string &label) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name, {.labelNames{label}});
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    void MetricService::IncrementGauge(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->inc((double) value);
        log_trace << "Gauge incremented, name: " << name;
    }

    void MetricService::IncrementGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name, labelName);
        }
        _gaugeMap[name]->labels({labelValue}).inc((double) value);
        log_trace << "Gauge incremented, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name, labelName);
        }
        _gaugeMap[name]->labels({labelValue}).set((double) value);
        log_trace << "Gauge value set, name: " << name << " label: " << labelValue;
    }

    void MetricService::SetGauge(const std::string &name, long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name, labelName);
        }
        _gaugeMap[name]->labels({labelValue}).set((double) value);
        log_trace << "Gauge value set, name: " << name << " label: " << labelValue;
    }

    void MetricService::SetGauge(const std::string &name, unsigned long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, unsigned long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name, labelName);
        }
        _gaugeMap[name]->labels({labelValue}).set((double) value);
        log_trace << "Gauge value set, name: " << name << " label: " << labelValue;
    }

    void MetricService::SetGauge(const std::string &name, float value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, float value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name, labelName);
        }
        _gaugeMap[name]->labels({labelValue}).set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, double value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set(value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name, labelName)) {
            AddGauge(name);
        }
        _gaugeMap[name]->labels({labelValue}).set(value);
        log_trace << "Gauge value set, name: " << name;
    }

    bool MetricService::GaugeExists(const std::string &name) {
        return _gaugeMap.find(name) != _gaugeMap.end();
    }

    bool MetricService::GaugeExists(const std::string &name, const std::string &label) {
        auto it = _gaugeMap.find(name);
        return it != _gaugeMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();
    }

    void MetricService::AddHistogram(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!HistogramExists(name)) {
            _histogramMap[name] = new Poco::Prometheus::Histogram(name);
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    void MetricService::AddHistogram(const std::string &name, const std::string &label) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!HistogramExists(name)) {
            _histogramMap[name] = new Poco::Prometheus::Histogram(name, {.labelNames{label}});
            log_trace << "Histogram added, name: " << name;
            return;
        }
        log_error << "Histogram exists already, name: " << name;
    }

    bool MetricService::HistogramExists(const std::string &name) {
        return _histogramMap.find(name) != _histogramMap.end();
    }

    bool MetricService::HistogramExists(const std::string &name, const std::string &label) {
        auto it = _histogramMap.find(name);
        return it != _histogramMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();
    }


    void MetricService::AddTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!TimerExists(name)) {
            _timerMap[name] = new Poco::Prometheus::Gauge(name);
            log_trace << "Timer added, name: " << name;
            return;
        }
        log_warning << "Timer exists already, name: " << name;
    }

    void MetricService::StartTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!TimerExists(name)) {
            _timerMap[name] = new Poco::Prometheus::Gauge(name);
        }
        if (_timerStartMap.find(GetTimerKey(name)) == _timerStartMap.end()) {
            _timerStartMap[GetTimerKey(name)] = std::chrono::high_resolution_clock::now();
            log_trace << "Timer started, name: " << name;
        }
    }

    void MetricService::StopTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (TimerExists(name)) {
            _timerMap.find(name)->second->set(TIME_DIFF(name));
        }
        auto it = _timerStartMap.find(GetTimerKey(name));
        if (it != _timerStartMap.end()) {
            _timerStartMap.erase(it);
        }
        log_trace << "Timer stopped, name: " << name;
    }

    bool MetricService::TimerExists(const std::string &name) {
        return _timerMap.find(name) != _timerMap.end();
    }

    void MetricService::ResetTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (TimerExists(name)) {
            StopTimer(name);
            _timerMap.find(name)->second->set(0.0);
        }
        log_trace << "Timer cleared, name: " << name;
    }

    void MetricService::ResetAllTimer() {
        Poco::Mutex::ScopedLock lock(_mutex);
        for (auto timer: _timerMap) {
            timer.second->set(0.0);
        }
    }

    std::string MetricService::GetTimerKey(const std::string &name) {
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        log_trace << "Timer key returned, name: " << name;
        return name + "::" + std::to_string(threadID);
    }
}// namespace AwsMock::Core