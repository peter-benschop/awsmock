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
        _server = std::make_shared<Poco::Prometheus::MetricsServer>(static_cast<Poco::UInt16>(_port));
        log_debug << "Prometheus manager initialized, port: " << _port;

        if (_server != nullptr) {
            _server->start();
        }
        log_info << "Monitoring manager started, port: " << _port;
    }

    void MetricService::Run() {
        log_trace << "Monitoring alive";
    }

    void MetricService::Shutdown() {
        _server->stop();
        log_info << "Metric module has been shutdown";
    }

    void MetricService::AddCounter(const std::string &name) {
        //boost::mutex::scoped_lock lock(_mutex);
        try {
            if (!CounterExists(name)) {
                _counterMap[name] = new Poco::Prometheus::Counter(name);
                _counterMap[name]->clear();
                log_trace << "Counter added, name: " << name;
                return;
            }
            log_error << "Gauge exists already, name: " << name;
        } catch (Poco::Exception &e) {
            log_error << e.message();
        }
    }

    void MetricService::AddCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        //boost::mutex::scoped_lock lock(_mutex);
        try {
            if (!CounterExists(name, labelName, labelValue)) {
                _counterMap[name] = new Poco::Prometheus::Counter(name, {.labelNames{labelName}});
                log_trace << "Counter added, name: " << name;
                return;
            }
            log_error << "Counter exists already, name: " << name;
        } catch (Poco::Exception &e) {
            log_error << e.message();
        }
    }

    bool MetricService::CounterExists(const std::string &name) {
        return _counterMap.find(name) != _counterMap.end();
    }

    bool MetricService::CounterExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_counterMap.begin(), _counterMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Counter *> obj) {
                   return obj.first == name && std::find(obj.second->labelNames().begin(), obj.second->labelNames().end(), labelName) != obj.second->labelNames().end();
               }) != _counterMap.end();
    }

    Poco::Prometheus::Counter *MetricService::GetCounter(const std::string &name) {
        auto it = _counterMap.find(name);
        if (it != _counterMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    Poco::Prometheus::Counter *MetricService::GetCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        auto it = std::find_if(_counterMap.begin(), _counterMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Counter *> obj) {
            return obj.first == name && std::find(obj.second->labelNames().begin(), obj.second->labelNames().end(), labelName) != obj.second->labelNames().end();
        });
        if (it != _counterMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    void MetricService::ClearCounter(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (CounterExists(name)) {
            auto counter = GetCounter(name);
            counter->clear();
            log_trace << "Counter cleared, name: " << name;
            return;
        }
        log_error << "Counter not found, name: " << name;
    }

    void MetricService::ClearCounter(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        boost::mutex::scoped_lock lock(_mutex);
        if (CounterExists(name, labelName, labelValue)) {
            auto counter = GetCounter(name);
            counter->clear();
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
        auto counter = GetCounter(name);
        counter->inc(value);
        log_trace << "Counter incremented, name: " << name;
    }

    void MetricService::IncrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!CounterExists(name, labelName, labelValue)) {
            AddCounter(name, labelName, labelValue);
        }
        _counterMap[name]->labels({labelValue}).inc((double) value);
        log_trace << "Counter incremented, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
    }

    void MetricService::AddGauge(const std::string &name) {
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
            _gaugeMap[name]->clear();
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    void MetricService::AddGauge(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        if (!GaugeExists(name)) {
            _gaugeMap[name] = new Poco::Prometheus::Gauge(name, {.labelNames{labelName}});
            log_trace << "Gauge added, name: " << name;
            return;
        }
        log_error << "Gauge exists already, name: " << name;
    }

    Poco::Prometheus::Gauge *MetricService::GetGauge(const std::string &name) {
        auto it = _gaugeMap.find(name);
        if (it != _gaugeMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    Poco::Prometheus::Gauge *MetricService::GetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        auto it = std::find_if(_gaugeMap.begin(), _gaugeMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Gauge *> obj) {
            return obj.first == name && std::find(obj.second->labelNames().begin(), obj.second->labelNames().end(), labelName) != obj.second->labelNames().end();
        });
        if (it != _gaugeMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    void MetricService::SetGauge(const std::string &name, double value) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name)) {
            AddGauge(name);
        }
        _gaugeMap[name]->set((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value) {
        boost::mutex::scoped_lock lock(_mutex);
        if (!GaugeExists(name, labelName, labelValue)) {
            AddGauge(name, labelName, labelValue);
        }
        _gaugeMap[name]->labels({labelValue}).inc((double) value);
        log_trace << "Gauge value set, name: " << name;
    }

    bool MetricService::GaugeExists(const std::string &name) {
        return _gaugeMap.find(name) != _gaugeMap.end();
    }

    bool MetricService::GaugeExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_gaugeMap.begin(), _gaugeMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Gauge *> &obj) {
                   return obj.first == name && std::find(obj.second->labelNames().begin(), obj.second->labelNames().end(), labelName) != obj.second->labelNames().end();
               }) != _gaugeMap.end();
    }

    void MetricService::AddTimer(const std::string &name) {
        try {
            if (!TimerExists(name)) {
                _timerMap[name] = new Poco::Prometheus::Gauge(name);
                _timerMap[name]->clear();
                log_trace << "Timer added, name: " << name;
                return;
            }
            log_error << "Timer exists already, name: " << name;
        } catch (Poco::Exception &e) {
            log_error << e.message();
        }
    }

    void MetricService::AddTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        try {
            if (!TimerExists(name, labelName, labelValue)) {
                _timerMap[GetTimerKey(name, labelName, labelValue)] = new Poco::Prometheus::Gauge(name, {.labelNames{labelName, labelValue}});
                log_trace << "Timer added, name: " << name;
                return;
            }
            log_error << "Timer exists already, name: " << name;
        } catch (Poco::Exception &e) {
            log_error << e.message();
        }
    }

    Poco::Prometheus::Gauge *MetricService::GetTimer(const std::string &name) {
        auto it = _timerMap.find(name);
        if (it != _timerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    Poco::Prometheus::Gauge *MetricService::GetTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        auto it = std::find_if(_timerMap.begin(), _timerMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Gauge *> &obj) {
            return obj.first == GetTimerKey(name, labelName, labelValue);
        });
        if (it != _timerMap.end()) {
            return it->second;
        }
        return nullptr;
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

            Poco::Prometheus::Gauge *timer = GetTimer(name);
            timer->set(TIME_DIFF_NAME(name));

            const auto count = std::erase_if(_timerStartMap, [name](const auto &item) {
                return item.first == GetTimerStartKey(name);
            });
            log_trace << "Timer stopped, name: " << name << " count: " << count << " size: " << _timerStartMap.size();
        } else {
            log_warning << "Timer not found, name: " << name;
        }
    }

    void MetricService::StopTimer(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        boost::mutex::scoped_lock lock(_mutex);
        if (TimerExists(name, labelName, labelValue)) {

            Poco::Prometheus::Gauge *timer = GetTimer(name, labelName, labelValue);
            timer->set(TIME_DIFF_LABEL(name, labelName, labelValue));

            std::erase_if(_timerStartMap, [name, labelName, labelValue](const auto &item) {
                return item.first == GetTimerStartKey(name, labelName, labelValue);
            });

            log_trace << "Timer stopped, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
        } else {
            log_trace << "Timer not found, name: " << name << " labelName: " << labelName << " labelValue: " << labelValue;
        }
    }

    bool MetricService::TimerExists(const std::string &name) {
        return _timerMap.find(name) != _timerMap.end();
    }

    bool MetricService::TimerExists(const std::string &name, const std::string &labelName, const std::string &labelValue) {
        return std::find_if(_timerMap.begin(), _timerMap.end(), [&name, &labelName, &labelValue](const std::pair<std::string, Poco::Prometheus::Gauge *> &obj) {
                   return obj.first == GetTimerKey(name, labelName, labelValue);
               }) != _timerMap.end();
    }

    void MetricService::ResetTimer(const std::string &name) {
        boost::mutex::scoped_lock lock(_mutex);
        if (TimerExists(name)) {
            Poco::Prometheus::Gauge *timer = GetTimer(name);
            timer->set(0.0);
        }
        log_trace << "Timer cleared, name: " << name;
    }

    void MetricService::ResetAllTimer() {
        boost::mutex::scoped_lock lock(_mutex);
        for (const auto &t: _timerMap) {
            Poco::Prometheus::Gauge *timer = GetTimer(t.first);
            if (timer) {
                timer->set(.0);
            }
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