//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/LambdaMemoryDb.h>

namespace AwsMock::Database {

  LambdaMemoryDb::LambdaMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool LambdaMemoryDb::LambdaExists(const std::string &function) {

    return find_if(_lambdas.begin(), _lambdas.end(), [function](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.function == function;
    }) != _lambdas.end();
  }

  bool LambdaMemoryDb::LambdaExists(const Entity::Lambda::Lambda &lambda) {

    std::string region = lambda.region;
    std::string function = lambda.function;
    return find_if(_lambdas.begin(), _lambdas.end(), [region, function](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.region == region && lambda.second.function == function;
    }) != _lambdas.end();
  }

  bool LambdaMemoryDb::LambdaExists(const std::string &region, const std::string &function, const std::string &runtime) {

    return find_if(_lambdas.begin(), _lambdas.end(), [region, function, runtime](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.region == region && lambda.second.function == function && lambda.second.runtime == runtime;
    }) != _lambdas.end();
  }

  bool LambdaMemoryDb::LambdaExistsByArn(const std::string &arn) {

    return find_if(_lambdas.begin(), _lambdas.end(), [arn](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.arn == arn;
    }) != _lambdas.end();
  }

  Entity::Lambda::LambdaList LambdaMemoryDb::ListLambdas(const std::string &region) {

    Entity::Lambda::LambdaList lambdaList;
    if (region.empty()) {
      for (const auto &lambda : _lambdas) {
        lambdaList.emplace_back(lambda.second);
      }
    } else {
      for (const auto &lambda : _lambdas) {
        if (lambda.second.region == region) {
          lambdaList.emplace_back(lambda.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got lambda list, size: " << lambdaList.size() << std::endl;
    return lambdaList;
  }

  Entity::Lambda::Lambda LambdaMemoryDb::CreateLambda(const Entity::Lambda::Lambda &lambda) {
    Poco::ScopedLock lock(_lambdaMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _lambdas[oid] = lambda;
    log_trace_stream(_logger) << "Lambda created, oid: " << oid << std::endl;
    return GetLambdaById(oid);
  }

  Entity::Lambda::Lambda LambdaMemoryDb::GetLambdaById(const std::string &oid) {

    auto it = find_if(_lambdas.begin(), _lambdas.end(), [oid](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.first == oid;
    });

    if (it == _lambdas.end()) {
      log_error_stream(_logger) << "Get lambda by ID failed, arn: " << oid << std::endl;
      throw Core::DatabaseException("Get lambda by ID failed, arn: "+oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  Entity::Lambda::Lambda LambdaMemoryDb::GetLambdaByArn(const std::string &arn) {

    auto it = find_if(_lambdas.begin(), _lambdas.end(), [arn](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.arn == arn;
    });

    if (it == _lambdas.end()) {
      log_error_stream(_logger) << "Get lambda by ARN failed, arn: " << arn << std::endl;
      throw Core::DatabaseException("Get lambda by ARN failed, arn: "+arn);
    }

    it->second.oid = arn;
    return it->second;
  }

  long LambdaMemoryDb::LambdaCount(const std::string &region) {

    long count = 0;
    if (region.empty()) {
      return static_cast<long>(_lambdas.size());
    } else {
      for (const auto &lambda : _lambdas) {
        if (lambda.second.region == region) {
          count++;
        }
      }
    }
    return count;
  }

  Entity::Lambda::Lambda LambdaMemoryDb::UpdateLambda(const Entity::Lambda::Lambda &lambda) {

    Poco::ScopedLock lock(_lambdaMutex);

    std::string region = lambda.region;
    std::string function = lambda.function;
    auto it = find_if(_lambdas.begin(), _lambdas.end(), [region, function](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.region == region && lambda.second.function == function;
    });

    if(it == _lambdas.end()) {
      log_error_stream(_logger) << "Update lambda failed, region: " << lambda.region << " function: " << lambda.function << std::endl;
      throw Core::DatabaseException("Update lambda failed, region: " + lambda.region + " function: " + lambda.function);
    }
    _lambdas[it->first] = lambda;
    return _lambdas[it->first];
  }

  void LambdaMemoryDb::DeleteLambda(const std::string &functionName) {
    Poco::ScopedLock lock(_lambdaMutex);

    const auto count = std::erase_if(_lambdas, [functionName](const auto &item) {
      auto const &[key, value] = item;
      return value.function == functionName;
    });
    log_debug_stream(_logger) << "Lambda deleted, count: " << count << std::endl;
  }

  void LambdaMemoryDb::DeleteAllLambdas() {
    Poco::ScopedLock lock(_lambdaMutex);

    log_debug_stream(_logger) << "All lambdas deleted, count: " << _lambdas.size() << std::endl;
    _lambdas.clear();
  }
}