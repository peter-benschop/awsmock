//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/CognitoMemoryDb.h>

namespace AwsMock::Database {

  CognitoMemoryDb::CognitoMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool CognitoMemoryDb::UserPoolExists(const std::string &region, const std::string &name) {

    return find_if(_cognitoUserPools.begin(), _cognitoUserPools.end(), [region, name](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
      return userPool.second.region == region && userPool.second.name == name;
    }) != _cognitoUserPools.end();
  }

  /*bool CognitoMemoryDb::CognitoExists(const Entity::Cognito::Cognito &cognito) {

    std::string region = cognito.region;
    std::string function = cognito.function;
    return find_if(_cognitos.begin(), _cognitos.end(), [region, function](const std::pair<std::string, Entity::Cognito::Cognito> &cognito) {
      return cognito.second.region == region && cognito.second.function == function;
    }) != _cognitos.end();
  }

  bool CognitoMemoryDb::CognitoExists(const std::string &region, const std::string &function, const std::string &runtime) {

    return find_if(_cognitos.begin(), _cognitos.end(), [region, function, runtime](const std::pair<std::string, Entity::Cognito::Cognito> &cognito) {
      return cognito.second.region == region && cognito.second.function == function && cognito.second.runtime == runtime;
    }) != _cognitos.end();
  }

  bool CognitoMemoryDb::CognitoExistsByArn(const std::string &arn) {

    return find_if(_cognitos.begin(), _cognitos.end(), [arn](const std::pair<std::string, Entity::Cognito::Cognito> &cognito) {
      return cognito.second.arn == arn;
    }) != _cognitos.end();
  }

  Entity::Cognito::CognitoList CognitoMemoryDb::ListCognitos(const std::string &region) {

    Entity::Cognito::CognitoList cognitoList;
    if (region.empty()) {
      for (const auto &cognito : _cognitos) {
        cognitoList.emplace_back(cognito.second);
      }
    } else {
      for (const auto &cognito : _cognitos) {
        if (cognito.second.region == region) {
          cognitoList.emplace_back(cognito.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got cognito list, size: " << cognitoList.size() << std::endl;
    return cognitoList;
  }*/

  Entity::Cognito::UserPool CognitoMemoryDb::CreateUserPool(const Entity::Cognito::UserPool &userPool) {
    Poco::ScopedLock lock(_cognitoMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _cognitoUserPools[oid] = userPool;
    log_trace_stream(_logger) << "Cognito user pool created, oid: " << oid << std::endl;
    return GetUserPoolByOid(oid);
  }

  Entity::Cognito::UserPool CognitoMemoryDb::GetUserPoolByOid(const std::string &oid) {

    auto it = find_if(_cognitoUserPools.begin(), _cognitoUserPools.end(), [oid](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
      return userPool.first == oid;
    });

    if (it == _cognitoUserPools.end()) {
      log_error_stream(_logger) << "Get cognito user pool by oid failed, arn: " << oid << std::endl;
      throw Core::DatabaseException("Get cognito user pool by oid failed, arn: " + oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  /*Entity::Cognito::Cognito CognitoMemoryDb::GetCognitoByArn(const std::string &arn) {

    auto it = find_if(_cognitos.begin(), _cognitos.end(), [arn](const std::pair<std::string, Entity::Cognito::Cognito> &cognito) {
      return cognito.second.arn == arn;
    });

    if (it == _cognitos.end()) {
      log_error_stream(_logger) << "Get cognito by ARN failed, arn: " << arn << std::endl;
      throw Core::DatabaseException("Get cognito by ARN failed, arn: "+arn);
    }

    it->second.oid = arn;
    return it->second;
  }

  long CognitoMemoryDb::CognitoCount(const std::string &region) {

    long count = 0;
    if (region.empty()) {
      return static_cast<long>(_cognitos.size());
    } else {
      for (const auto &cognito : _cognitos) {
        if (cognito.second.region == region) {
          count++;
        }
      }
    }
    return count;
  }

  Entity::Cognito::Cognito CognitoMemoryDb::UpdateCognito(const Entity::Cognito::Cognito &cognito) {

    Poco::ScopedLock lock(_cognitoMutex);

    std::string region = cognito.region;
    std::string function = cognito.function;
    auto it = find_if(_cognitos.begin(), _cognitos.end(), [region, function](const std::pair<std::string, Entity::Cognito::Cognito> &cognito) {
      return cognito.second.region == region && cognito.second.function == function;
    });

    if(it == _cognitos.end()) {
      log_error_stream(_logger) << "Update cognito failed, region: " << cognito.region << " function: " << cognito.function << std::endl;
      throw Core::DatabaseException("Update cognito failed, region: " + cognito.region + " function: " + cognito.function);
    }
    _cognitos[it->first] = cognito;
    return _cognitos[it->first];
  }

  void CognitoMemoryDb::DeleteCognito(const std::string &functionName) {
    Poco::ScopedLock lock(_cognitoMutex);

    const auto count = std::erase_if(_cognitos, [functionName](const auto &item) {
      auto const &[key, value] = item;
      return value.function == functionName;
    });
    log_debug_stream(_logger) << "Cognito deleted, count: " << count << std::endl;
  }

  void CognitoMemoryDb::DeleteAllCognitos() {
    Poco::ScopedLock lock(_cognitoMutex);

    log_debug_stream(_logger) << "All cognitos deleted, count: " << _cognitos.size() << std::endl;
    _cognitos.clear();
  }*/
}