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
    DefineStringProperty("awsmock.region", "AWSMOCK_REGION", "eu-central-1");
    DefineStringProperty("awsmock.account.id", "AWSMOCK_ACCOUNT_ID", "000000000000");
    DefineStringProperty("awsmock.client.id", "AWSMOCK_CLIENT_ID", "00000000");
    DefineStringProperty("awsmock.user", "AWSMOCK_USER", "none");
    DefineStringProperty("awsmock.data.dir", "AWSMOCK_DATA_DIR", "/tmp/awsmock/data");
    DefineBoolProperty("awsmock.pretty", "AWSMOCK_PRETTY", false);

    // Manager
    DefineStringProperty("awsmock.manager.host", "AWSMOCK_MANAGER_HOST", "localhost");
    DefineIntProperty("awsmock.manager.port", "AWSMOCK_MANAGER_PORT", 4567);
    DefineIntProperty("awsmock.manager.max.queue", "AWSMOCK_MANAGER_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.manager.max.threads", "AWSMOCK_MANAGER_MAX_THREADS", 50);

    // Gateway
    DefineStringProperty("awsmock.service.gateway.host", "AWSMOCK_SERVICE_GATEWAY_HOST", "localhost");
    DefineIntProperty("awsmock.service.gateway.port", "AWSMOCK_SERVICE_GATEWAY_PORT", 4566);
    DefineIntProperty("awsmock.service.gateway.max.queue", "AWSMOCK_SERVICE_GATEWAY_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.gateway.max.threads", "AWSMOCK_SERVICE_GATEWAY_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.gateway.timeout", "AWSMOCK_SERVICE_GATEWAY_TIMEOUT", 900);

    // S3
    DefineBoolProperty("awsmock.service.s3.active", "AWSMOCK_SERVICE_S3_ACTIVE", true);
    DefineStringProperty("awsmock.service.s3.host", "AWSMOCK_SERVICE_S3_HOST", "localhost");
    DefineIntProperty("awsmock.service.s3.port", "AWSMOCK_SERVICE_S3_PORT", 9500);
    DefineIntProperty("awsmock.service.s3.max.queue", "AWSMOCK_SERVICE_S3_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.s3.max.threads", "AWSMOCK_SERVICE_S3_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.s3.timeout", "AWSMOCK_SERVICE_S3_TIMEOUT", 900);
    DefineStringProperty("awsmock.service.s3.data.dir", "AWSMOCK_SERVICE_S3_DATA_DIR", "tmp/awsmock/data/s3");
    DefineIntProperty("awsmock.service.s3.period", "AWSMOCK_SERVICE_S3_PERIOD", 60000);

    // SQS
    DefineBoolProperty("awsmock.service.sqs.active", "AWSMOCK_SERVICE_SQS_ACTIVE", true);
    DefineStringProperty("awsmock.service.sqs.host", "AWSMOCK_SERVICE_SQS_HOST", "localhost");
    DefineIntProperty("awsmock.service.sqs.port", "AWSMOCK_SERVICE_SQS_PORT", 9501);
    DefineIntProperty("awsmock.service.sqs.max.queue", "AWSMOCK_SERVICE_SQS_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.sqs.max.threads", "AWSMOCK_SERVICE_SQS_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.sqs.timeout", "AWSMOCK_SERVICE_SQS_TIMEOUT", 900);
    DefineIntProperty("awsmock.service.sqs.period", "AWSMOCK_SERVICE_SQS_PERIOD", 60000);

    // SNS
    DefineBoolProperty("awsmock.service.sns.active", "AWSMOCK_SERVICE_SNS_ACTIVE", true);
    DefineStringProperty("awsmock.service.sns.host", "AWSMOCK_SERVICE_SNS_HOST", "localhost");
    DefineIntProperty("awsmock.service.sns.port", "AWSMOCK_SERVICE_SNS_PORT", 9502);
    DefineIntProperty("awsmock.service.sns.max.queue", "AWSMOCK_SERVICE_SNS_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.sns.max.threads", "AWSMOCK_SERVICE_SNS_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.sns.timeout", "AWSMOCK_SERVICE_SNS_TIMEOUT", 900);
    DefineIntProperty("awsmock.service.sns.period", "AWSMOCK_SERVICE_SNS_PERIOD", 60000);

    // Lambda
    DefineBoolProperty("awsmock.service.lambda.active", "AWSMOCK_SERVICE_LAMBDA_ACTIVE", true);
    DefineStringProperty("awsmock.service.lambda.host", "AWSMOCK_SERVICE_LAMBDA_HOST", "localhost");
    DefineIntProperty("awsmock.service.lambda.port", "AWSMOCK_SERVICE_LAMBDA_PORT", 9503);
    DefineIntProperty("awsmock.service.lambda.max.queue", "AWSMOCK_SERVICE_LAMBDA_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.lambda.max.threads", "AWSMOCK_SERVICE_LAMBDA_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.lambda.timeout", "AWSMOCK_SERVICE_LAMBDA_TIMEOUT", 900);
    DefineIntProperty("awsmock.service.lambda.period", "AWSMOCK_SERVICE_LAMBDA_PERIOD", 60000);

    // Transfer server
    DefineBoolProperty("awsmock.service.transfer.active", "AWSMOCK_SERVICE_TRANSFER_ACTIVE", true);
    DefineStringProperty("awsmock.service.transfer.host", "AWSMOCK_SERVICE_TRANSFER_HOST", "localhost");
    DefineIntProperty("awsmock.service.transfer.port", "AWSMOCK_SERVICE_TRANSFER_PORT", 9504);
    DefineIntProperty("awsmock.service.transfer.max.queue", "AWSMOCK_SERVICE_TRANSFER_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.transfer.max.threads", "AWSMOCK_SERVICE_TRANSFER_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.transfer.timeout", "AWSMOCK_SERVICE_TRANSFER_TIMEOUT", 900);
    DefineIntProperty("awsmock.service.transfer.ftp.port", "AWSMOCK_SERVICE_TRANSFER_FTP_PORT", 2121);
    DefineStringProperty("awsmock.service.transfer.bucket", "AWSMOCK_SERVICE_TRANSFER_BUCKET", "transfer-server");
    DefineStringProperty("awsmock.service.transfer.base.dir", "AWSMOCK_SERVICE_TRANSFER_BASE_DIR", "/tmp/awsmock/data/transfer");
    DefineIntProperty("awsmock.service.transfer.period", "AWSMOCK_SERVICE_TRANSFER_PERIOD", 60000);

    // Cognito
    DefineBoolProperty("awsmock.service.cognito.active", "AWSMOCK_SERVICE_COGNITO_ACTIVE", true);
    DefineStringProperty("awsmock.service.cognito.host", "AWSMOCK_SERVICE_COGNITO_HOST", "localhost");
    DefineIntProperty("awsmock.service.cognito.port", "AWSMOCK_SERVICE_COGNITO_PORT", 9505);
    DefineIntProperty("awsmock.service.cognito.max.queue", "AWSMOCK_SERVICE_COGNITO_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.cognito.max.threads", "AWSMOCK_SERVICE_COGNITO_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.cognito.timeout", "AWSMOCK_SERVICE_COGNITO_TIMEOUT", 120);
    DefineIntProperty("awsmock.service.cognito.period", "AWSMOCK_SERVICE_COGNITO_PERIOD", 10000);

    // DynamoDB
    DefineBoolProperty("awsmock.service.dynamodb.active", "AWSMOCK_SERVICE_DYNAMODB_ACTIVE", true);
    DefineStringProperty("awsmock.service.dynamodb.host", "AWSMOCK_SERVICE_DYNAMODB_HOST", "localhost");
    DefineIntProperty("awsmock.service.dynamodb.port", "AWSMOCK_SERVICE_DYNAMODB_PORT", 9506);
    DefineIntProperty("awsmock.service.dynamodb.max.queue", "AWSMOCK_SERVICE_DYNAMODB_MAX_QUEUE", 250);
    DefineIntProperty("awsmock.service.dynamodb.max.threads", "AWSMOCK_SERVICE_DYNAMODB_MAX_THREADS", 50);
    DefineIntProperty("awsmock.service.dynamodb.timeout", "AWSMOCK_SERVICE_DYNAMODB_TIMEOUT", 120);
    DefineIntProperty("awsmock.service.dynamodb.period", "AWSMOCK_SERVICE_DYNAMODB_PERIOD", 10000);

    // Docker
    DefineStringProperty("awsmock.docker.network.mode", "AWSMOCK_DOCKER_NETWORK_MODE", "bridge");
    DefineStringProperty("awsmock.docker.network.name", "AWSMOCK_DOCKER_NETWORK_NAME", ".dockerhost.net");
    DefineIntProperty("awsmock.docker.default.memory.size", "AWSMOCK_DOCKER_DEFAULT_MEMORY_SIZE", 512);
    DefineIntProperty("awsmock.docker.default.temp.size", "AWSMOCK_DOCKER_DEFAULT_TEMP_SIZE", 10240);
    DefineIntProperty("awsmock.docker.container.port", "AWSMOCK_DOCKER_CONTAINER_PORT", 8080);

    // Monitoring
    DefineIntProperty("awsmock.monitoring.port", "AWSMOCK_CORE_METRIC_PORT",  8081);
    DefineIntProperty("awsmock.monitoring.timeout", "AWSMOCK_CORE_METRIC_TIMEOUT", 60000);

    // Logging
    DefineStringProperty("awsmock.log.level", "AWSMOCK_LOG_LEVEL", "information");

    // Database
    DefineBoolProperty("awsmock.mongodb.active", "AWSMOCK_MONGODB_ACTIVE", true);
    DefineStringProperty("awsmock.mongodb.name", "AWSMOCK_MONGODB_NAME", "awsmock");
    DefineStringProperty("awsmock.mongodb.host", "AWSMOCK_MONGODB_HOST", "localhost");
    DefineIntProperty("awsmock.mongodb.port", "AWSMOCK_MONGODB_PORT", 27017);
    DefineStringProperty("awsmock.mongodb.user", "AWSMOCK_MONGODB_USER", "awsmock");
    DefineStringProperty("awsmock.mongodb.password", "AWSMOCK_MONGODB_PASSWORD", "awsmock");
  }

  void Configuration::DefineStringProperty(const std::string &key, const std::string &envProperty, const std::string &defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setString(key, getenv(envProperty.c_str()));
    } else if (!has(key)) {
      setString(key, defaultValue);
    }
    log_trace_stream(_logger) << "Defined property, key: " << key << " property: " << envProperty << " default: " << defaultValue << std::endl;
  }

  void Configuration::DefineBoolProperty(const std::string &key, const std::string &envProperty, bool defaultValue) {
    if (getenv(envProperty.c_str()) != nullptr) {
      setBool(key, std::string(getenv(envProperty.c_str())) == "true");
    } else if (!has(key)) {
      setBool(key, defaultValue);
    }
    log_trace_stream(_logger) << "Defined property, key: " << key << " property: " << envProperty << " default: " << defaultValue << std::endl;
  }

  void Configuration::DefineIntProperty(const std::string &key, const std::string &envProperty, int defaultValue) {
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
