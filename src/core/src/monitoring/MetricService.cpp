//
// Created by vogje01 on 07/01/2023.
//

#include "awsmock/core/MetricService.h"

namespace AwsMock::Core {

  MetricService::MetricService(const Configuration &configuration) : MetricService(configuration.getInt("awsmock.monitoring.port"), configuration.getInt("awsmock.monitoring.timeout")) {}

  MetricService::MetricService(int port, long timeout) : _logger(Poco::Logger::get("MetricService")), _port(port), _timeout(timeout) {}

  void MetricService::Initialize() {
    _server = std::make_shared<Poco::Prometheus::MetricsServer>(_port);
    _metricSystemTimer = std::make_shared<Poco::Timer>(0, _timeout);
    _metricSystemCollector = std::make_shared<MetricSystemCollector>();
    log_debug_stream(_logger) << "Prometheus manager initialized, port: " << _port << std::endl;
  }

  [[maybe_unused]] void MetricService::StartServer() {
    StartSystemCounter();
    if (_server != nullptr) {
      _server->start();
    }
    log_info_stream(_logger) << "Monitoring manager started, port: " << _port << std::endl;;
  }

  void MetricService::ShutdownServer() {
    /*if (_metricSystemTimer != nullptr) {
      _metricSystemTimer->stop();
    }*/
    if (_server != nullptr) {
      _server->stop();
      _server.reset();
    }
    log_info_stream(_logger) << "Metric module has been shutdown" << std::endl;
  }

  void MetricService::AddCounter(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name)) {
      _counterMap[name] = new Poco::Prometheus::Counter(name);
      _counterMap[name]->clear();
      log_trace_stream(_logger) << "Counter added, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Gauge exists already, name: " + name << std::endl;
  }

  void MetricService::AddCounter(const std::string &name, const std::string &label) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name, label)) {
      std::vector<std::string> labels;
      labels.push_back(label);
      _counterMap[name] = new Poco::Prometheus::Counter(name);
      _counterMap[name]->labelNames(labels);
      _counterMap[name]->clear();
      log_trace_stream(_logger) << "Counter added, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Gauge exists already, name: " + name << std::endl;
  }

  bool MetricService::CounterExists(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    auto it = _counterMap.find(name);
    return it != _counterMap.end();
  }

  bool MetricService::CounterExists(const std::string &name, const std::string &label) {
    Poco::Mutex::ScopedLock lock(_mutex);
    auto it = _counterMap.find(name);
    return it != _counterMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();
  }

  void MetricService::ClearCounter(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (CounterExists(name)) {
      _counterMap[name]->clear();
      log_trace_stream(_logger) << "Counter cleared, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Counter not found, name: " + name << std::endl;
  }

  void MetricService::IncrementCounter(const std::string &name, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name)) {
      AddCounter(name);
    }
    _counterMap[name]->inc((double) value);
    log_trace_stream(_logger) << "Counter incremented, name: " + name << std::endl;
  }

  void MetricService::IncrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name, labelName)) {
      AddCounter(name, labelName);
    }
    _counterMap[name]->labels({labelValue}).inc((double) value);
    log_trace_stream(_logger) << "Counter incremented, name: " + name << " labelName: " << labelName << " labelValue: " << labelValue << std::endl;
  }

  void MetricService::DecrementCounter(const std::string &name, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name)) {
      AddCounter(name);
    }
    _counterMap[name]->inc((double) -value);
    log_trace_stream(_logger) << "Counter incremented, name: " + name << std::endl;
  }

  void MetricService::DecrementCounter(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!CounterExists(name, labelName)) {
      AddCounter(name, labelName);
    }
    _counterMap[name]->labels({labelValue}).inc((double) -value);
    log_trace_stream(_logger) << "Counter incremented, name: " + name << std::endl;
  }

  void MetricService::AddGauge(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
      log_trace_stream(_logger) << "Gauge added, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Gauge exists already, name: " + name << std::endl;
  }

  void MetricService::AddGauge(const std::string &name, const std::string &label) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      std::vector<std::string> labels;
      labels.push_back(label);
      _gaugeMap[name] = new Poco::Prometheus::Gauge(name);
      _gaugeMap[name]->labelNames(labels);
      log_trace_stream(_logger) << "Gauge added, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Gauge exists already, name: " + name << std::endl;
  }

  void MetricService::IncrementGauge(const std::string &name, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->inc((double) value);
    log_trace_stream(_logger) << "Gauge incremented, name: " + name << std::endl;
  }

  void MetricService::IncrementGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).inc((double) value);
    log_trace_stream(_logger) << "Gauge incremented, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, int value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, long value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, long value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, unsigned long value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, unsigned long value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, float value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, float value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).set((double) value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, double value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name)) {
      AddGauge(name);
    }
    _gaugeMap[name]->set(value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  void MetricService::SetGauge(const std::string &name, const std::string &labelName, const std::string &labelValue, double value) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!GaugeExists(name, labelName)) {
      AddGauge(name, labelName);
    }
    _gaugeMap[name]->labels({labelValue}).set(value);
    log_trace_stream(_logger) << "Gauge value set, name: " + name << std::endl;
  }

  bool MetricService::GaugeExists(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    auto it = _gaugeMap.find(name);
    return it != _gaugeMap.end();
  }

  bool MetricService::GaugeExists(const std::string &name, const std::string &label) {
    Poco::Mutex::ScopedLock lock(_mutex);
    auto it = _gaugeMap.find(name);
    return it != _gaugeMap.end() && std::find(it->second->labelNames().begin(), it->second->labelNames().end(), label) != it->second->labelNames().end();
  }

  void MetricService::AddTimer(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!TimerExists(name)) {
      _timerMap[name] = new Poco::Prometheus::Gauge(name);
      log_trace_stream(_logger) << "Timer added, name: " + name << std::endl;
      return;
    }
    log_error_stream(_logger) << "Timer exists already, name: " + name << std::endl;
  }

  void MetricService::StartTimer(const std::string &name) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (!TimerExists(name)) {
      AddTimer(name);
    }
    if (_timerStartMap.find(GetTimerKey(name)) == _timerStartMap.end()) {
      _timerStartMap[GetTimerKey(name)] = std::chrono::high_resolution_clock::now();
      log_trace_stream(_logger) << "Timer started, name: " + name << std::endl;
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
    log_trace_stream(_logger) << "Timer stopped, name: " + name << std::endl;
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
    log_trace_stream(_logger) << "Timer cleared, name: " + name << std::endl;
  }

  void MetricService::ResetAllTimer() {
    Poco::Mutex::ScopedLock lock(_mutex);
    for (auto timer : _timerMap) {
      timer.second->set(0.0);
    }
  }

  std::string MetricService::GetTimerKey(const std::string &name) {
    uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    log_trace_stream(_logger) << "Timer key returned, name: " + name << std::endl;
    return name + "::" + std::to_string(threadID);
  }

  void MetricService::StartSystemCounter() {
    if (_metricSystemTimer != nullptr && _metricSystemCollector != nullptr) {
      _metricSystemTimer->start(Poco::TimerCallback<MetricSystemCollector>(*_metricSystemCollector, &MetricSystemCollector::onTimer));
      log_debug_stream(_logger) << "System collector started, timeout: " << _timeout << "ms" << std::endl;
    } else {
      log_error_stream(_logger) << "Metric system timer not defined" << std::endl;
    }
  }
}