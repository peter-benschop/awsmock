//
// Created by vogje01 on 22/08/2022.
//

#include "awsmock/core/Configuration.h"

namespace AwsMock::Core {

  Configuration::Configuration() : _logger(Poco::Logger::get("Configuration")) {
    Initialize();
  }

  Configuration::Configuration(const std::string &filename) : _logger(Poco::Logger::get("Configuration")) {
    SetFilename(filename);
    Initialize();
  }

  void Configuration::Initialize() {

    // Monitoring
    DefineProperty("awsmock.monitoring.port", "AWSMOCK_CORE_METRIC_PORT", "8081");
    DefineProperty("awsmock.monitoring.timeout", "AWSMOCK_CORE_METRIC_TIMEOUT", "60000");

    // Logging
    DefineProperty("awsmock.log.level", "AWSMOCK_CORE_LOG_LEVEL", "information");
  }

  void Configuration::DefineProperty(const std::string &key, const std::string &envProperty, const std::string &defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setString(key, getenv(envProperty.c_str()));
    } else if (!has(key)) {
      setString(key, defaultValue);
    }
    log_trace_stream(_logger) << "Defined property, key: " << key << " property: " << envProperty << " default: " << defaultValue << std::endl;
  }

  std::string Configuration::GetFilename() const {
    if (_filename.empty()) {
      throw CoreException("Filename not set");
    }
    return _filename;
  }

  void Configuration::SetFilename(const std::string &filename) {
    if (filename.empty()) {
      throw CoreException("Empty filename");
    }
    _filename = filename;
    load(_filename);
  }

  int Configuration::GetMetricPort() const {
    if (!hasProperty("awsmock.monitoring.port")) {
      throw CoreException("Property not found, key: awsmock.prometheus.port");
    }
    return getInt("awsmock.monitoring.port");
  }

  long Configuration::GetMetricTimeout() const {
    if (!hasProperty("awsmock.monitoring.timeout")) {
      throw CoreException("Property not found, key: awsmock.monitoring.timeout");
    }
    return getInt("awsmock.monitoring.timeout");
  }

  std::string Configuration::GetLogLevel() const {
    if (!hasProperty("awsmock.log.level")) {
      throw CoreException("Property not found, key: awsmock.log.level");
    }
    return getString("awsmock.log.level");
  }

  void Configuration::SetLogLevel(const std::string &logLevel) {
    setString("awsmock.log.level", logLevel);
  }

  void Configuration::SetValue(const std::string &key, const std::string &value) {
    if (!hasProperty(key)) {
      throw CoreException("Property not found, key: " + key);
    }
    setString(key, value);
    log_trace_stream(_logger) << "Value set, key: " << key << std::endl;
  }

  void Configuration::SetValue(const std::string &key, bool value) {
    if (!hasProperty(key)) {
      throw CoreException("Property not found, key: " + key);
    }
    setBool(key, value);
    log_trace_stream(_logger) << "Value set, key: " << key << std::endl;
  }

  void Configuration::SetValue(const std::string &key, int value) {
    if (!hasProperty(key)) {
      throw CoreException("Property not found, key: " + key);
    }
    setInt(key, value);
    log_trace_stream(_logger) << "Value set, key: " << key << std::endl;
  }

  std::string Configuration::GetAppName() {
    return PROJECT_NAME;
  }

  std::string Configuration::GetVersion() {
    return PROJECT_VER;
  }

  std::string Configuration::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  void Configuration::WriteFile(const std::string &filename) {
    std::vector<std::string> pKeys;
    this->keys(pKeys);
    std::ofstream ofs(filename, std::ofstream::trunc);
    for (const auto &key : *this) {
      ofs << key.first << "=" << key.second << std::endl;
    }
  }

  std::ostream &operator<<(std::ostream &os, const Configuration &s) {
    os << "Configuration={";
    for (const auto &it : s) {
      os << it.first << "={" << it.second + "}, ";
    }
    return os;
  }

} // namespace AwsMock::Core
