//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/TransferMemoryDb.h>

namespace AwsMock::Database {

  TransferMemoryDb::TransferMemoryDb() : _logger(Poco::Logger::get("TransferMemoryDb")) {}

  std::vector<Entity::Transfer::Transfer> TransferMemoryDb::ListServers(const std::string &region) {

    Entity::Transfer::TransferList transferList;
    for (const auto &transfer : _transfers) {
      transferList.emplace_back(transfer.second);
    }

    log_trace_stream(_logger) << "Got transfer list, size: " << transferList.size() << std::endl;
    return transferList;
  }
}