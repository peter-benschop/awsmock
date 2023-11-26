//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/CognitoMemoryDb.h>

namespace AwsMock::Database {

  CognitoMemoryDb::CognitoMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool CognitoMemoryDb::UserPoolExists(const std::string &region, const std::string &name) {

    return find_if(_userPools.begin(), _userPools.end(), [region, name](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
      return userPool.second.region == region && userPool.second.name == name;
    }) != _userPools.end();
  }

  bool CognitoMemoryDb::UserPoolExists(const std::string &id) {

    return find_if(_userPools.begin(), _userPools.end(), [id](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
      return userPool.second.id == id;
    }) != _userPools.end();
  }

  Entity::Cognito::UserPoolList CognitoMemoryDb::ListUserPools(const std::string &region) {

    Entity::Cognito::UserPoolList userPoolList;
    if (region.empty()) {
      for (const auto &userPool : _userPools) {
        userPoolList.emplace_back(userPool.second);
      }
    } else {
      for (const auto &userPool : _userPools) {
        if (userPool.second.region == region) {
          userPoolList.emplace_back(userPool.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got user pool list, size: " << userPoolList.size() << std::endl;
    return userPoolList;
  }

  Entity::Cognito::UserPool CognitoMemoryDb::CreateUserPool(const Entity::Cognito::UserPool &userPool) {
    Poco::ScopedLock lock(_userPoolMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _userPools[oid] = userPool;
    log_trace_stream(_logger) << "Cognito user pool created, oid: " << oid << std::endl;
    return GetUserPoolByOid(oid);
  }

  Entity::Cognito::UserPool CognitoMemoryDb::GetUserPoolByOid(const std::string &oid) {

    auto it = find_if(_userPools.begin(), _userPools.end(), [oid](const std::pair<std::string, Entity::Cognito::UserPool> &userPool) {
      return userPool.first == oid;
    });

    if (it == _userPools.end()) {
      log_error_stream(_logger) << "Get cognito user pool by oid failed, arn: " << oid << std::endl;
      throw Core::DatabaseException("Get cognito user pool by oid failed, arn: " + oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  /*

  Entity::Cognito::Cognito CognitoMemoryDb::UpdateCognito(const Entity::Cognito::Cognito &cognito) {

    Poco::ScopedLock lock(_userPoolMutex);

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
*/
  void CognitoMemoryDb::DeleteUserPool(const std::string &id) {
    Poco::ScopedLock lock(_userPoolMutex);

    const auto count = std::erase_if(_userPools, [id](const auto &item) {
      auto const &[key, value] = item;
      return value.id == id;
    });
    log_debug_stream(_logger) << "Cognito user pool deleted, count: " << count << std::endl;
  }

  void CognitoMemoryDb::DeleteAllUserPools() {
    Poco::ScopedLock lock(_userPoolMutex);

    log_debug_stream(_logger) << "All cognito user pools deleted, count: " << _userPools.size() << std::endl;
    _userPools.clear();
  }

}