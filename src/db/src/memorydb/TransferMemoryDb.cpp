//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/TransferMemoryDb.h>

namespace AwsMock::Database {

  TransferMemoryDb::TransferMemoryDb() : _logger(Poco::Logger::get("TransferMemoryDb")) {}

  bool TransferMemoryDb::TransferExists(const std::string &region, const std::string &serverId) {

    return find_if(_transfers.begin(), _transfers.end(), [region, serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.region == region && transfer.second.serverId == serverId;
    }) != _transfers.end();
  }

  std::vector<Entity::Transfer::Transfer> TransferMemoryDb::ListServers(const std::string &region) {

    Entity::Transfer::TransferList transferList;
    for (const auto &transfer : _transfers) {
      transferList.emplace_back(transfer.second);
    }

    log_trace_stream(_logger) << "Got transfer list, size: " << transferList.size() << std::endl;
    return transferList;
  }
}