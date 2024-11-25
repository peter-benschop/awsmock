//
// Created by vogje01 on 22/08/2022.
//

#include <awsmock/core/config/YamlConfiguration.h>

namespace AwsMock::Core {
boost::mutex YamlConfiguration::_configurationMutex;

YamlConfiguration::YamlConfiguration() { Initialize(); }

YamlConfiguration::YamlConfiguration(const std::string &basename) {
  Initialize();
  SetFilename(basename);
}

void YamlConfiguration::Initialize() {
  // General
  DefineStringProperty("awsmock.region", "AWSMOCK_REGION", "eu-central-1");
  DefineStringProperty("awsmock.account.id", "AWSMOCK_ACCOUNT_ID",
                       "000000000000");
  DefineStringProperty("awsmock.client.id", "AWSMOCK_CLIENT_ID", "00000000");
  DefineStringProperty("awsmock.user", "AWSMOCK_USER", "none");
  DefineStringProperty("awsmock.data.dir", "AWSMOCK_DATA_DIR",
                       "/tmp/awsmock/data");
  DefineStringProperty("awsmock.temp.dir", "AWSMOCK_TEMP_DIR",
                       "/tmp/awsmock/tmp");
  DefineBoolProperty("awsmock.pretty", "AWSMOCK_PRETTY", false);
  DefineBoolProperty("awsmock.verifysignature", "AWSMOCK_VERIFY_SIGNATURE",
                     false);
  DefineBoolProperty("awsmock.dockerized", "AWSMOCK_DOCKERIZED", false);

  // Manager
  DefineStringProperty("awsmock.manager.http.host", "AWSMOCK_MANAGER_HOST",
                       "localhost");
  DefineIntProperty("awsmock.manager.http.port", "AWSMOCK_MANAGER_PORT", 4567);
  DefineIntProperty("awsmock.manager.http.max.queue",
                    "AWSMOCK_MANAGER_MAX_QUEUE", 50);
  DefineIntProperty("awsmock.manager.http.max.threads",
                    "AWSMOCK_MANAGER_MAX_THREADS", 10);

  // Gateway
  DefineBoolProperty("awsmock.service.gateway.active",
                     "AWSMOCK_SERVICE_GATEWAY_ACTIVE", true);
  DefineStringProperty("awsmock.service.gateway.http.host",
                       "AWSMOCK_SERVICE_GATEWAY_HOST", "localhost");
  DefineIntProperty("awsmock.service.gateway.http.port",
                    "AWSMOCK_SERVICE_GATEWAY_PORT", 4566);
  DefineIntProperty("awsmock.service.gateway.http.max.queue",
                    "AWSMOCK_SERVICE_GATEWAY_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.gateway.http.max.threads",
                    "AWSMOCK_SERVICE_GATEWAY_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.gateway.http.timeout",
                    "AWSMOCK_SERVICE_GATEWAY_TIMEOUT", 900);

  // S3
  DefineBoolProperty("awsmock.service.s3.active", "AWSMOCK_SERVICE_S3_ACTIVE",
                     true);
  DefineStringProperty("awsmock.service.s3.http.host",
                       "AWSMOCK_SERVICE_S3_HOST", "localhost");
  DefineIntProperty("awsmock.service.s3.http.port", "AWSMOCK_SERVICE_S3_PORT",
                    9500);
  DefineIntProperty("awsmock.service.s3.http.max.queue",
                    "AWSMOCK_SERVICE_S3_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.s3.http.max.threads",
                    "AWSMOCK_SERVICE_S3_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.s3.http.timeout",
                    "AWSMOCK_SERVICE_S3_TIMEOUT", 900);
  DefineIntProperty("awsmock.service.s3.monitoring.period",
                    "AWSMOCK_SERVICE_S3_MONITORING_PERIOD", 900);

  // SQS
  DefineBoolProperty("awsmock.service.sqs.active", "AWSMOCK_SERVICE_SQS_ACTIVE",
                     true);
  DefineStringProperty("awsmock.service.sqs.http.host",
                       "AWSMOCK_SERVICE_SQS_HOST", "localhost");
  DefineIntProperty("awsmock.service.sqs.http.port", "AWSMOCK_SERVICE_SQS_PORT",
                    9501);
  DefineIntProperty("awsmock.service.sqs.http.max.queue",
                    "AWSMOCK_SERVICE_SQS_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.sqs.http.max.threads",
                    "AWSMOCK_SERVICE_SQS_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.sqs.http.timeout",
                    "AWSMOCK_SERVICE_SQS_TIMEOUT", 900);
  DefineStringProperty("awsmock.service.sqs.hostname",
                       "AWSMOCK_SERVICE_SQS_HOSTNAME", "localstack");
  DefineIntProperty("awsmock.service.s3.monitoring.period",
                    "AWSMOCK_MONITORING_SQS_PERIOD", 300);
  DefineIntProperty("awsmock.service.s3.worker.period",
                    "AWSMOCK_WORKER_SQS_PERIOD", 30);

  // SNS
  DefineBoolProperty("awsmock.service.sns.active", "AWSMOCK_SERVICE_SNS_ACTIVE",
                     true);
  DefineStringProperty("awsmock.service.sns.http.host",
                       "AWSMOCK_SERVICE_SNS_HOST", "localhost");
  DefineIntProperty("awsmock.service.sns.http.port", "AWSMOCK_SERVICE_SNS_PORT",
                    9502);
  DefineIntProperty("awsmock.service.sns.http.max.queue",
                    "AWSMOCK_SERVICE_SNS_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.sns.http.max.threads",
                    "AWSMOCK_SERVICE_SNS_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.sns.http.timeout",
                    "AWSMOCK_SERVICE_SNS_TIMEOUT", 900);
  DefineIntProperty("awsmock.service.sns.message.timeout",
                    "AWSMOCK_SERVICE_SNS_MESSAGE_TIMEOUT", 14);
  DefineIntProperty("awsmock.monitoring.sns.worker.period",
                    "AWSMOCK_SNS_WORKER_PERIOD", 300);
  DefineIntProperty("awsmock.monitoring.sns.monitoring.period",
                    "AWSMOCK_SNS_MONITORING_PERIOD", 300);

  // Lambda
  DefineBoolProperty("awsmock.service.lambda.active",
                     "AWSMOCK_SERVICE_LAMBDA_ACTIVE", true);
  DefineStringProperty("awsmock.service.lambda.http.host",
                       "AWSMOCK_SERVICE_LAMBDA_HOST", "localhost");
  DefineIntProperty("awsmock.service.lambda.http.port",
                    "AWSMOCK_SERVICE_LAMBDA_PORT", 9503);
  DefineIntProperty("awsmock.service.lambda.http.max.queue",
                    "AWSMOCK_SERVICE_LAMBDA_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.lambda.http.max.threads",
                    "AWSMOCK_SERVICE_LAMBDA_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.lambda.http.timeout",
                    "AWSMOCK_SERVICE_LAMBDA_TIMEOUT", 900);
  DefineIntProperty("awsmock.monitoring.lambda.period",
                    "AWSMOCK_MONITORING_LAMBDA_PERIOD", 300);

  // Transfer server
  DefineBoolProperty("awsmock.service.transfer.active",
                     "AWSMOCK_SERVICE_TRANSFER_ACTIVE", true);
  DefineStringProperty("awsmock.service.transfer.http.host",
                       "AWSMOCK_SERVICE_TRANSFER_HOST", "localhost");
  DefineIntProperty("awsmock.service.transfer.http.port",
                    "AWSMOCK_SERVICE_TRANSFER_PORT", 9504);
  DefineIntProperty("awsmock.service.transfer.http.max.queue",
                    "AWSMOCK_SERVICE_TRANSFER_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.transfer.http.max.threads",
                    "AWSMOCK_SERVICE_TRANSFER_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.transfer.http.timeout",
                    "AWSMOCK_SERVICE_TRANSFER_TIMEOUT", 900);
  DefineIntProperty("awsmock.service.transfer.ftp.port",
                    "AWSMOCK_SERVICE_TRANSFER_FTP_PORT", 21);
  DefineStringProperty("awsmock.service.transfer.bucket",
                       "AWSMOCK_SERVICE_TRANSFER_BUCKET", "transfer-server");
  DefineStringProperty("awsmock.service.transfer.base.dir",
                       "AWSMOCK_SERVICE_TRANSFER_BASE_DIR",
                       "/tmp/awsmock/data/transfer");
  DefineIntProperty("awsmock.service.transfer.monitoring.period",
                    "AWSMOCK_SERVICE_TRANSFER_MONITORING_PERIOD", 300);

  // Cognito
  DefineBoolProperty("awsmock.service.cognito.active",
                     "AWSMOCK_SERVICE_COGNITO_ACTIVE", true);
  DefineStringProperty("awsmock.service.cognito.http.host",
                       "AWSMOCK_SERVICE_COGNITO_HOST", "localhost");
  DefineIntProperty("awsmock.service.cognito.http.port",
                    "AWSMOCK_SERVICE_COGNITO_PORT", 9505);
  DefineIntProperty("awsmock.service.cognito.http.max.queue",
                    "AWSMOCK_SERVICE_COGNITO_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.cognito.http.max.threads",
                    "AWSMOCK_SERVICE_COGNITO_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.cognito.http.timeout",
                    "AWSMOCK_SERVICE_COGNITO_TIMEOUT", 120);
  DefineIntProperty("awsmock.service.cognito.monitoring.period",
                    "AWSMOCK_SERVICE_COGNITO_MONITORING_PERIOD", 300);

  // DynamoDB
  DefineBoolProperty("awsmock.service.dynamodb.active",
                     "AWSMOCK_SERVICE_DYNAMODB_ACTIVE", true);
  DefineStringProperty("awsmock.service.dynamodb.http.host",
                       "AWSMOCK_SERVICE_DYNAMODB_HOST", "localhost");
  DefineIntProperty("awsmock.service.dynamodb.http.port",
                    "AWSMOCK_SERVICE_DYNAMODB_PORT", 9506);
  DefineIntProperty("awsmock.service.dynamodb.http.max.queue",
                    "AWSMOCK_SERVICE_DYNAMODB_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.dynamodb.http.max.threads",
                    "AWSMOCK_SERVICE_DYNAMODB_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.dynamodb.http.timeout",
                    "AWSMOCK_SERVICE_DYNAMODB_TIMEOUT", 120);
  DefineIntProperty("awsmock.service.dynamodb.monitoring.period",
                    "AWSMOCK_MONITORING_DYNAMODB_PERIOD", 300);
  DefineStringProperty("awsmock.dynamodb.host", "AWSMOCK_DYNAMODB_HOST",
                       "localhost");
  DefineIntProperty("awsmock.dynamodb.port", "AWSMOCK_DYNAMODB_PORT", 8000);

  // SecretsManager
  DefineBoolProperty("awsmock.service.secretsmanager.active",
                     "AWSMOCK_SERVICE_SECRETSMANAGER_ACTIVE", true);
  DefineStringProperty("awsmock.service.secretsmanager.http.host",
                       "AWSMOCK_SERVICE_SECRETSMANAGER_HOST", "localhost");
  DefineIntProperty("awsmock.service.secretsmanager.http.port",
                    "AWSMOCK_SERVICE_SECRETSMANAGER_PORT", 9507);
  DefineIntProperty("awsmock.service.secretsmanager.http.max.queue",
                    "AWSMOCK_SERVICE_SECRETSMANAGER_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.secretsmanager.http.max.threads",
                    "AWSMOCK_SERVICE_SECRETSMANAGER_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.secretsmanager.http.timeout",
                    "AWSMOCK_SERVICE_SECRETSMANAGER_TIMEOUT", 120);
  DefineIntProperty("awsmock.service.secretsmanager.monitoring.period",
                    "AWSMOCK_SERVICE_SECRETSMANAGER_MONITORING_PERIOD", 300);

  // KMS
  DefineBoolProperty("awsmock.service.kms.active", "AWSMOCK_SERVICE_KMS_ACTIVE",
                     true);
  DefineStringProperty("awsmock.service.kms.http.host",
                       "AWSMOCK_SERVICE_KMS_HOST", "localhost");
  DefineIntProperty("awsmock.service.kms.http.port", "AWSMOCK_SERVICE_KMS_PORT",
                    9508);
  DefineIntProperty("awsmock.service.kms.http.max.queue",
                    "AWSMOCK_SERVICE_KMS_MAX_QUEUE", 250);
  DefineIntProperty("awsmock.service.kms.http.max.threads",
                    "AWSMOCK_SERVICE_KMS_MAX_THREADS", 50);
  DefineIntProperty("awsmock.service.kms.http.timeout",
                    "AWSMOCK_SERVICE_KMS_TIMEOUT", 900);
  DefineIntProperty("awsmock.service.kms.monitoring.period",
                    "AWSMOCK_SERVICEK_KMS_MONITORING_PERIOD", 300);
  DefineIntProperty("awsmock.service.kms.worker.period",
                    "AWSMOCK_WORKER_KMS_PERIOD", 300);

  // Docker
  DefineBoolProperty("awsmock.docker.active", "AWSMOCK_DOCKER_ACTIVE", false);
  DefineStringProperty("awsmock.docker.network.mode",
                       "AWSMOCK_DOCKER_NETWORK_MODE", "local");
  DefineIntProperty("awsmock.docker.default.memory.size",
                    "AWSMOCK_DOCKER_DEFAULT_MEMORY_SIZE", 512);
  DefineIntProperty("awsmock.docker.default.temp.size",
                    "AWSMOCK_DOCKER_DEFAULT_TEMP_SIZE", 10240);
  DefineIntProperty("awsmock.docker.container.port",
                    "AWSMOCK_DOCKER_CONTAINER_PORT", 8080);
  DefineStringProperty("awsmock.docker.socket", "AWSMOCK_DOCKER_SOCKET",
                       "/var/run/docker.sock");

  // Podman
  DefineBoolProperty("awsmock.podman.active", "AWSMOCK_PODMAN_ACTIVE", true);
  DefineStringProperty("awsmock.podman.network.mode",
                       "AWSMOCK_PODMAN_NETWORK_MODE", "local");
  DefineIntProperty("awsmock.podman.default.memory.size",
                    "AWSMOCK_PODMAN_DEFAULT_MEMORY_SIZE", 512);
  DefineIntProperty("awsmock.podman.default.temp.size",
                    "AWSMOCK_PODMAN_DEFAULT_TEMP_SIZE", 10240);
  DefineIntProperty("awsmock.podman.container.port",
                    "AWSMOCK_PODMAN_CONTAINER_PORT", 8080);
  DefineStringProperty("awsmock.podman.socket", "AWSMOCK_PODMAN_SOCKET",
                       "/run/podman/podman.sock");

  // FTP server
  DefineIntProperty("awsmock.service.ftp.port", "AWSMOCK_SERVICE_FTP_ACTIVE",
                    21);
  DefineStringProperty("awsmock.service.ftp.host", "AWSMOCK_SERVICE_FTP_HOST",
                       "localhost");
  DefineIntProperty("awsmock.service.ftp.max.thread",
                    "AWSMOCK_SERVICE_FTP_MAX_THREADS", 4);
  DefineStringProperty("awsmock.service.ftp.base.dir",
                       "AWSMOCK_SERVICE_FTP_BASE_DIR",
                       "/home/awsmock/data/transfer");
  DefineIntProperty("awsmock.service.ftp.pasv.min",
                    "AWSMOCK_SERVICE_FTP_PASV_MIN", 6000);
  DefineIntProperty("awsmock.service.ftp.pasv.max",
                    "AWSMOCK_SERVICE_FTP_PASV_MAX", 6010);
  DefineStringProperty("awsmock.service.ftp.address",
                       "AWSMOCK_SERVICE_FTP_ADDRESS", "::");

  // Monitoring
  DefineIntProperty("awsmock.service.monitoring.port",
                    "AWSMOCK_CORE_METRIC_PORT", 9091);
  DefineIntProperty("awsmock.service.monitoring.timeout",
                    "AWSMOCK_CORE_METRIC_TIMEOUT", 60000);

  // Logging
  DefineStringProperty("awsmock.service.logging.level", "AWSMOCK_LOG_LEVEL",
                       "info");
  DefineStringProperty("awsmock.service.logging.file", "AWSMOCK_LOG_FILE",
                       "/var/run/awsmock.log");

  // Database
  DefineBoolProperty("awsmock.mongodb.active", "AWSMOCK_MONGODB_ACTIVE", true);
  DefineStringProperty("awsmock.mongodb.name", "AWSMOCK_MONGODB_NAME",
                       "awsmock");
  DefineStringProperty("awsmock.mongodb.host", "AWSMOCK_MONGODB_HOST",
                       "localhost");
  DefineIntProperty("awsmock.mongodb.port", "AWSMOCK_MONGODB_PORT", 27017);
  DefineStringProperty("awsmock.mongodb.user", "AWSMOCK_MONGODB_USER", "root");
}

void YamlConfiguration::DefineStringProperty(const std::string &key,
                                             const std::string &envProperty,
                                             const std::string &defaultValue) {
  if (getenv(envProperty.c_str()) != nullptr) {
    _yamlConfig[key] = envProperty.c_str();
    AddToEnvList(key, getenv(envProperty.c_str()));
  } else /*if (!HasProperty(key))*/ {
    _yamlConfig[key] = defaultValue;
  }
  log_trace << "Defined property, key: " << key << " property: " << envProperty
            << " default: " << defaultValue;
}

void YamlConfiguration::DefineBoolProperty(const std::string &key,
                                           const std::string &envProperty,
                                           const bool defaultValue) {
  if (getenv(envProperty.c_str()) != nullptr) {
    _yamlConfig[key] = envProperty.c_str();
    AddToEnvList(key, getenv(envProperty.c_str()));
  } else /*if (!HasProperty(key))*/ {
    _yamlConfig[key] = defaultValue;
  }
  log_trace << "Defined property, key: " << key << " property: " << envProperty
            << " default: " << defaultValue;
}

void YamlConfiguration::DefineIntProperty(const std::string &key,
                                          const std::string &envProperty,
                                          int defaultValue) {
  if (getenv(envProperty.c_str()) != nullptr) {
    _yamlConfig[key] = envProperty.c_str();
    AddToEnvList(key, getenv(envProperty.c_str()));
  } else /*if (!HasProperty(key))*/ {
    _yamlConfig[key] = defaultValue;
  }
  log_trace << "Defined property, key: " << key << " property: " << envProperty
            << " default: " << defaultValue;
}

std::string YamlConfiguration::GetFilename() const {
  if (_filename.empty()) {
    throw CoreException("Filename not set");
  }
  return _filename;
}

void YamlConfiguration::SetFilename(const std::string &filename) {
  if (filename.empty()) {
    throw CoreException("Empty filename");
  }
  if (!FileUtils::FileExists(filename)) {
    log_warning << "Configuration file '" << filename
                << "' does not exist. Will use default.";
  }

  // Save file name
  _filename = filename;

  // Parse YAML file
  _yamlConfig = YAML::LoadFile(filename);

  // Reapply environment settings
  ApplyEnvSettings();

  log_debug << ToString();
}

void YamlConfiguration::SetValue(const std::string &key,
                                 const std::string &value) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  const YAML::Node node = lookup(_yamlConfig, paths.begin(), paths.end());
  node.as<std::string>() = value;
  log_trace << "Value set, key: " << key;
}

void YamlConfiguration::SetValueByPath(const std::string &path,
                                       const std::string &value) {
  std::vector<std::string> paths = StringUtils::Split(path, '.');
  if (paths.size() == 1) {
    _yamlConfig[path[0]].as<std::string>() = value;
  }
  if (paths.size() == 2) {
    _yamlConfig[path[0]][path[1]].as<std::string>() = value;
  }
  if (paths.size() == 3) {
    _yamlConfig[path[0]][path[1]][path[2]].as<std::string>() = value;
  }
  log_trace << "Value set, key: " << path;
}

void YamlConfiguration::SetValue(const std::string &key, const bool value) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  const YAML::Node node = lookup(_yamlConfig, paths.begin(), paths.end());
  node.as<std::string>() = std::to_string(value);
  log_trace << "Value set, key: " << key;
}

void YamlConfiguration::SetValue(const std::string &key, const int value) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  const YAML::Node node = lookup(_yamlConfig, paths.begin(), paths.end());
  node.as<std::string>() = std::to_string(value);
  log_trace << "Value set, key: " << key;
}

std::string YamlConfiguration::GetValueString(const std::string &key) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  return lookup(_yamlConfig, paths.begin(), paths.end()).as<std::string>();
}

int YamlConfiguration::GetValueInt(const std::string &key) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  return lookup(_yamlConfig, paths.begin(), paths.end()).as<int>();
}

long YamlConfiguration::GetValueLong(const std::string &key) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  return lookup(_yamlConfig, paths.begin(), paths.end()).as<long>();
}

bool YamlConfiguration::GetValueBool(const std::string &key) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  return lookup(_yamlConfig, paths.begin(), paths.end()).as<bool>();
}

double YamlConfiguration::GetValueDouble(const std::string &key) {
  if (!HasProperty(key)) {
    throw CoreException("Property not found, key: " + key);
  }
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  return lookup(_yamlConfig, paths.begin(), paths.end()).as<double>();
}

std::string YamlConfiguration::GetAppName() { return PROJECT_NAME; }

std::string YamlConfiguration::GetVersion() { return PROJECT_VERSION; }

std::string YamlConfiguration::ToString() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

void YamlConfiguration::WriteFile(const std::string &filename) const {
  std::ofstream ofs(filename);
  ofs << _yamlConfig;
  ofs.close();
}

void YamlConfiguration::AddToEnvList(const std::string &key,
                                     const std::string &value) {
  _envList[key] = value;
}

void YamlConfiguration::ApplyEnvSettings() const {
  for (const auto &[fst, snd] : _envList) {
    // SetValue(fst, snd);
  }
}

bool YamlConfiguration::HasProperty(const std::string &key) {
  std::vector<std::string> paths = StringUtils::Split(key, '.');
  YAML::Node traverse = _yamlConfig;
  for (std::string &path_element : paths) {
    traverse.reset(traverse[path_element]);
  }
  return traverse.IsDefined();
}

std::ostream &operator<<(std::ostream &os, const YamlConfiguration &s) {
  os << "Configuration={";
  //        for (const auto &it: s) {
  //            os << it.first << " = " << it.second + ", ";
  //        }
  return os;
}
} // namespace AwsMock::Core
