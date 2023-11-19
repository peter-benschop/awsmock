//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/LambdaMemoryDb.h>

namespace AwsMock::Database {

  LambdaMemoryDb::LambdaMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

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

  long LambdaMemoryDb::LambdaCount(const std::string &region) {

    long count = 0;
    if (region.empty()) {
      return _lambdas.size();
    } else {
      for (const auto &lambda : _lambdas) {
        if (lambda.second.region == region) {
          count++;
        }
      }
    }
    return count;
  }
}