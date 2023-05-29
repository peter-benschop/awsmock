//
// Created by vogje01 on 07/01/2023.
//

#include "awsmock/core/MetricService.h"

namespace AwsMock::Core {

    MetricService::MetricService(const Configuration &configuration) : MetricService(configuration.GetMetricPort(), configuration.GetMetricTimeout()) {}

    MetricService::MetricService(int port, long timeout) : _logger(Poco::Logger::get("root")), _port(port), _timeout(timeout) {}

    MetricService::~MetricService() {
        // Delete counters
        for (auto &it : _counterMap) {
            delete it.second;
        }
        // Delete gauges
        for (auto &it : _gaugeMap) {
            delete it.second;
        }
        for (auto &it : _timerMap) {
            delete it.second;
        }
        if(_server != nullptr) {
            _server->stop();
        }
        if(_metricSystemTimer != nullptr) {
            _metricSystemTimer->stop();
        }
        _timerStartMap.clear();
        delete _server;
        delete _metricSystemTimer;
        delete _metricSystemCollector;
        poco_debug(_logger, "MetricService cleaned up");
    }

    [[maybe_unused]]
    void MetricService::Initialize() {
        _server = new Poco::Prometheus::MetricsServer(_port);
        _metricSystemTimer = new Poco::Timer(0, _timeout);
        _metricSystemCollector = new MetricSystemCollector();
        poco_debug(_logger, "Prometheus server initialized, port: " + std::to_string(_port));
    }

    [[maybe_unused]] void MetricService::StartServer() {
        StartSystemCounter();
        if (_server != nullptr) {
            _server->start();
        }
        poco_information(_logger, "Monitoring server started, port: " + std::to_string(_port));
    }

    void MetricService::ShutdownServer() {
        poco_debug(_logger, "Starting MetricService shutdown");
        if (_server != nullptr) {
            _server->stop();
        }
        if (_metricSystemTimer != nullptr) {
            _metricSystemTimer->stop();
        }
    }

    void MetricService::AddCounter(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name)) {
            _counterMap[name] = new Poco::Prometheus::Counter(name);
            _counterMap[name]->clear();
            poco_trace(_logger, "Counter added, name: " + name);
            return;
        }
        poco_error(_logger, "Gauge exists already, name: " + name);
    }

    bool MetricService::CounterExists(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        auto it = _counterMap.find(name);
        return it != _counterMap.end();
    }

    void MetricService::ClearCounter(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (CounterExists(name)) {
            _counterMap[name]->clear();
            poco_trace(_logger, "Counter cleared, name: " + name);
            return;
        }
        poco_error(_logger, "Counter not found, name: " + name);
    }

    void MetricService::IncrementCounter(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!CounterExists(name)) {
            AddCounter(name);
        }
        _counterMap[name]->inc((double) value);
        poco_trace(_logger, "Counter incremented, name: " + name);
    }

    void MetricService::AddGauge(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
            poco_trace(_logger, "Gauge added, name: " + name);
            return;
        }
        poco_error(_logger, "Gauge exists already, name: " + name);
    }

    void MetricService::IncrementGauge(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->inc((double) value);
        poco_trace(_logger, "Gauge incremented, name: " + name);
    }

    void MetricService::SetGauge(const std::string &name, int value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        poco_trace(_logger, "Gauge value set, name: " + name);
    }

    void MetricService::SetGauge(const std::string &name, long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        poco_trace(_logger, "Gauge value set, name: " + name);
    }

    void MetricService::SetGauge(const std::string &name, unsigned long value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        poco_trace(_logger, "Gauge value set, name: " + name);
    }

    void MetricService::SetGauge(const std::string &name, float value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        poco_trace(_logger, "Gauge value set, name: " + name);
    }

    void MetricService::SetGauge(const std::string &name, double value) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set(value);
        poco_trace(_logger, "Gauge value set, name: " + name);
    }

    bool MetricService::GaugeExists(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        auto it = _gaugeMap.find(name);
        return it != _gaugeMap.end();
    }

    void MetricService::AddTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!TimerExists(name)) {
            _timerMap[name] = new Poco::Prometheus::Gauge(name);
            poco_trace(_logger, "Timer added, name: " + name);
            return;
        }
        poco_error(_logger, "Timer exists already, name: " + name);
    }

    void MetricService::StartTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (!TimerExists(name)) {
            AddTimer(name);
        }
        if (_timerStartMap.find(GetTimerKey(name)) == _timerStartMap.end()) {
            _timerStartMap[GetTimerKey(name)] = std::chrono::high_resolution_clock::now();
            poco_trace(_logger, "Timer started, name: " + name);
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
        poco_trace(_logger, "Timer stopped, name: " + name);
    }

    bool MetricService::TimerExists(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        return _timerMap.find(name) != _timerMap.end();
    }

    void MetricService::ResetTimer(const std::string &name) {
        Poco::Mutex::ScopedLock lock(_mutex);
        if (TimerExists(name)) {
            StopTimer(name);
            _timerMap.find(name)->second->set(0.0);
        }
        poco_trace(_logger, "Timer cleared, name: " + name);
    }

    void MetricService::ResetAllTimer() {
        Poco::Mutex::ScopedLock lock(_mutex);
        for (auto timer : _timerMap) {
            timer.second->set(0.0);
        }
    }

    std::string MetricService::GetTimerKey(const std::string &name) {
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        poco_trace(_logger, "Timer key returned, name: " + name);
        return name + "::" + std::to_string(threadID);
    }

    void MetricService::StartSystemCounter() {
        if (_metricSystemTimer != nullptr && _metricSystemCollector != nullptr) {
            _metricSystemTimer->start(Poco::TimerCallback<MetricSystemCollector>(*_metricSystemCollector, &MetricSystemCollector::onTimer));
            poco_debug(_logger, "System collector started, timeout: " + std::to_string(_timeout) + "ms");
        } else {
            poco_error(_logger, "Metric system timer not defined");
        }
    }
}