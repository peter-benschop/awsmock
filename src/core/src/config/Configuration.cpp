//
// Created by vogje01 on 22/08/2022.
//

#include <awsmock/core/Configuration.h>

namespace AwsMock::Core {

  Configuration::Configuration() : _logger(Poco::Logger::get("Configuration")) {
    Initialize();
  }

  Configuration::Configuration(const std::string &filename) : _logger(Poco::Logger::get("Configuration")) {
    SetFilename(filename);
    Initialize();
  }

  void Configuration::Initialize() {

    // General
    DefineProperty("awsmock.region", "AWSMOCK_REGION", "eu-central-1");
    DefineProperty("awsmock.account.id", "AWSMOCK_ACCOUNT_ID", "000000000000");
    DefineProperty("awsmock.client.id", "AWSMOCK_CLIENT_ID", "00000000");
    DefineProperty("awsmock.user", "AWSMOCK_USER", "none");
    DefineProperty("awsmock.data.dir", "AWSMOCK_DATA_DIR", "/tmp/awsmock/data");
    DefineProperty("awsmock.pretty", "AWSMOCK_PRETTY", false);

    // Manager
    DefineProperty("awsmock.manager.host", "AWSMOCK_MANAGER_HOST", "localhost");
    DefineProperty("awsmock.manager.port", "AWSMOCK_MANAGER_PORT", 4567);
    DefineProperty("awsmock.manager.max.queue", "AWSMOCK_MANAGER_MAX_QUEUE", 250);
    DefineProperty("awsmock.manager.max.threads", "AWSMOCK_MANAGER_MAX_THREADS", 50);

    // Gateway
    DefineProperty("awsmock.service.gateway.host", "AWSMOCK_SERVICE_GATEWAY_HOST", "localhost");
    DefineProperty("awsmock.service.gateway.port", "AWSMOCK_SERVICE_GATEWAY_PORT", 4566);
    DefineProperty("awsmock.service.gateway.max.queue", "AWSMOCK_SERVICE_GATEWAY_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.gateway.max.threads", "AWSMOCK_SERVICE_GATEWAY_MAX_THREADS", 50);
    DefineProperty("awsmock.service.gateway.timeout", "AWSMOCK_SERVICE_GATEWAY_TIMEOUT", 900);

    // S3
    DefineProperty("awsmock.service.s3.active", "AWSMOCK_SERVICE_S3_ACTIVE", true);
    DefineProperty("awsmock.service.s3.host", "AWSMOCK_SERVICE_S3_HOST", "localhost");
    DefineProperty("awsmock.service.s3.port", "AWSMOCK_SERVICE_S3_PORT", 9500);
    DefineProperty("awsmock.service.s3.max.queue", "AWSMOCK_SERVICE_S3_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.s3.max.threads", "AWSMOCK_SERVICE_S3_MAX_THREADS", 50);
    DefineProperty("awsmock.service.s3.timeout", "AWSMOCK_SERVICE_S3_TIMEOUT", 900);
    DefineProperty("awsmock.service.s3.data.dir", "AWSMOCK_SERVICE_S3_DATA_DIR", "tmp/awsmock/data/s3");
    DefineProperty("awsmock.service.s3.period", "AWSMOCK_SERVICE_S3_PERIOD", 60000);

    // SQS
    DefineProperty("awsmock.service.sqs.active", "AWSMOCK_SERVICE_SQS_ACTIVE", true);
    DefineProperty("awsmock.service.sqs.host", "AWSMOCK_SERVICE_SQS_HOST", "localhost");
    DefineProperty("awsmock.service.sqs.port", "AWSMOCK_SERVICE_SQS_PORT", 9501);
    DefineProperty("awsmock.service.sqs.max.queue", "AWSMOCK_SERVICE_SQS_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.sqs.max.threads", "AWSMOCK_SERVICE_SQS_MAX_THREADS", 50);
    DefineProperty("awsmock.service.sqs.timeout", "AWSMOCK_SERVICE_SQS_TIMEOUT", 900);
    DefineProperty("awsmock.service.sqs.period", "AWSMOCK_SERVICE_SQS_PERIOD", 60000);

    // SNS
    DefineProperty("awsmock.service.sns.active", "AWSMOCK_SERVICE_SNS_ACTIVE", true);
    DefineProperty("awsmock.service.sns.host", "AWSMOCK_SERVICE_SNS_HOST", "localhost");
    DefineProperty("awsmock.service.sns.port", "AWSMOCK_SERVICE_SNS_PORT", 9502);
    DefineProperty("awsmock.service.sns.max.queue", "AWSMOCK_SERVICE_SNS_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.sns.max.threads", "AWSMOCK_SERVICE_SNS_MAX_THREADS", 50);
    DefineProperty("awsmock.service.sns.timeout", "AWSMOCK_SERVICE_SNS_TIMEOUT", 900);
    DefineProperty("awsmock.service.sns.period", "AWSMOCK_SERVICE_SNS_PERIOD", 60000);

    // Lambda
    DefineProperty("awsmock.service.lambda.active", "AWSMOCK_SERVICE_LAMBDA_ACTIVE", true);
    DefineProperty("awsmock.service.lambda.host", "AWSMOCK_SERVICE_LAMBDA_HOST", "localhost");
    DefineProperty("awsmock.service.lambda.port", "AWSMOCK_SERVICE_LAMBDA_PORT", 9503);
    DefineProperty("awsmock.service.lambda.max.queue", "AWSMOCK_SERVICE_LAMBDA_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.lambda.max.threads", "AWSMOCK_SERVICE_LAMBDA_MAX_THREADS", 50);
    DefineProperty("awsmock.service.lambda.timeout", "AWSMOCK_SERVICE_LAMBDA_TIMEOUT", 900);
    DefineProperty("awsmock.service.lambda.period", "AWSMOCK_SERVICE_LAMBDA_PERIOD", 60000);

    // Transfer server
    DefineProperty("awsmock.service.transfer.active", "AWSMOCK_SERVICE_TRANSFER_ACTIVE", true);
    DefineProperty("awsmock.service.transfer.host", "AWSMOCK_SERVICE_TRANSFER_HOST", "localhost");
    DefineProperty("awsmock.service.transfer.port", "AWSMOCK_SERVICE_TRANSFER_PORT", 9504);
    DefineProperty("awsmock.service.transfer.max.queue", "AWSMOCK_SERVICE_TRANSFER_MAX_QUEUE", 250);
    DefineProperty("awsmock.service.transfer.max.threads", "AWSMOCK_SERVICE_TRANSFER_MAX_THREADS", 50);
    DefineProperty("awsmock.service.transfer.timeout", "AWSMOCK_SERVICE_TRANSFER_TIMEOUT", 900);
    DefineProperty("awsmock.service.transfer.ftp.port", "AWSMOCK_SERVICE_TRANSFER_FTP_PORT", 2121);
    DefineProperty("awsmock.service.transfer.bucket", "AWSMOCK_SERVICE_TRANSFER_BUCKET", "transfer-server");
    DefineProperty("awsmock.service.transfer.base.dir", "AWSMOCK_SERVICE_TRANSFER_BASE_DIR", "/tmp/awsmock/data/transfer");
    DefineProperty("awsmock.service.transfer.period", "AWSMOCK_SERVICE_TRANSFER_PERIOD", 60000);

    // Monitoring
    DefineProperty("awsmock.monitoring.port", "AWSMOCK_CORE_METRIC_PORT", "8081");
    DefineProperty("awsmock.monitoring.timeout", "AWSMOCK_CORE_METRIC_TIMEOUT", "60000");

    // Logging
    DefineProperty("awsmock.log.level", "AWSMOCK_CORE_LOG_LEVEL", "information");

    // Database
    DefineProperty("awsmock.mongodb.active", "AWSMOCK_DATABASE_ACTIVE", true);
  }

  void Configuration::DefineProperty(const std::string &key, const std::string &envProperty, const std::string &defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setString(key, getenv(envProperty.c_str()));
    } else if (!has(key)) {
      setString(key, defaultValue);
    }
    log_trace_stream(_logger) << "Defined property, key: " << key << " property: " << envProperty << " default: " << defaultValue << std::endl;
  }

  void Configuration::DefineProperty(const std::string &key, const std::string &envProperty, bool defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setBool(key, std::string(getenv(envProperty.c_str())) == "true");
    } else if (!has(key)) {
      setBool(key, defaultValue);
    }
    log_trace_stream(_logger) << "Defined property, key: " << key << " property: " << envProperty << " default: " << defaultValue << std::endl;
  }

  void Configuration::DefineProperty(const std::string &key, const std::string &envProperty, int defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setInt(key, std::stoi(getenv(envProperty.c_str())));
    } else if (!has(key)) {
      setInt(key, defaultValue);
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
