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

  bool TransferMemoryDb::TransferExists(const Entity::Transfer::Transfer &transfer) {

    return TransferExists(transfer.region, transfer.serverId);

  }

  bool TransferMemoryDb::TransferExists(const std::string &serverId) {

    return find_if(_transfers.begin(), _transfers.end(), [serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.serverId == serverId;
    }) != _transfers.end();

  }

  bool TransferMemoryDb::TransferExists(const std::string &region, const std::vector<std::string> &protocols) {

    return find_if(_transfers.begin(), _transfers.end(), [region, protocols](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.region == region && transfer.second.protocols == protocols;
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

  Entity::Transfer::Transfer TransferMemoryDb::CreateTransfer(const Entity::Transfer::Transfer &transfer) {
    Poco::ScopedLock lock(_transferMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _transfers[oid] = transfer;
    log_trace_stream(_logger) << "Transfer created, oid: " << oid << std::endl;
    return GetTransferById(oid);
  }

  Entity::Transfer::Transfer TransferMemoryDb::UpdateTransfer(const Entity::Transfer::Transfer &transfer) {
    Poco::ScopedLock lock(_transferMutex);

    std::string region = transfer.region;
    std::string serverId = transfer.serverId;
    auto it = find_if(_transfers.begin(), _transfers.end(), [region, serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.region == region && transfer.second.serverId == serverId;
    });

    if (it == _transfers.end()) {
      log_error_stream(_logger) << "Update transfer failed, serverId: " << serverId << std::endl;
      throw Core::DatabaseException("Update transfer failed, serverId: " + serverId);
    }

    _transfers[it->first] = transfer;
    return _transfers[it->first];

  }

  Entity::Transfer::Transfer TransferMemoryDb::GetTransferById(const std::string &oid) {

    auto it = find_if(_transfers.begin(), _transfers.end(), [oid](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.first == oid;
    });

    if (it == _transfers.end()) {
      log_error_stream(_logger) << "Get transfer by ID failed, oid: " << oid << std::endl;
      throw Core::DatabaseException("Get transfer by ID failed, oid: " + oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  Entity::Transfer::Transfer TransferMemoryDb::GetTransferByServerId(const std::string &serverId) {

    auto it = find_if(_transfers.begin(), _transfers.end(), [serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.serverId == serverId;
    });

    if (it == _transfers.end()) {
      log_error_stream(_logger) << "Get transfer by serverId failed, serverId: " << serverId << std::endl;
      throw Core::DatabaseException("Get transfer by serverId failed, serverId: " + serverId);
    }

    it->second.oid = it->first;
    return it->second;
  }

  Entity::Transfer::Transfer TransferMemoryDb::GetTransferByArn(const std::string &arn) {

    auto it = find_if(_transfers.begin(), _transfers.end(), [arn](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
      return transfer.second.arn == arn;
    });

    if (it == _transfers.end()) {
      log_error_stream(_logger) << "Get transfer by arn failed, arn: " << arn << std::endl;
      throw Core::DatabaseException("Get transfer by arn failed, arn: " + arn);
    }

    it->second.oid = it->first;
    return it->second;
  }

  void TransferMemoryDb::DeleteTransfer(const std::string &serverId) {
    Poco::ScopedLock lock(_transferMutex);

    const auto count = std::erase_if(_transfers, [serverId](const auto &item) {
      auto const &[key, value] = item;
      return value.serverId == serverId;
    });
    log_debug_stream(_logger) << "Transfer server deleted, count: " << count << std::endl;
  }

  void TransferMemoryDb::DeleteAllTransfers() {
    Poco::ScopedLock lock(_transferMutex);

    log_debug_stream(_logger) << "All transfer servers deleted, count: " << _transfers.size() << std::endl;
    _transfers.clear();
  }
}