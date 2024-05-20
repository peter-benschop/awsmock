//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/TransferMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex TransferMemoryDb::_transferMutex;
    Poco::Mutex TransferMemoryDb::_userMutex;

    bool TransferMemoryDb::TransferExists(const std::string &region, const std::string &serverId) {

        return find_if(_transfers.begin(),
                       _transfers.end(),
                       [region, serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                           return transfer.second.region == region && transfer.second.serverId == serverId;
                       }) != _transfers.end();
    }

    bool TransferMemoryDb::TransferExists(const Entity::Transfer::Transfer &transfer) {

        return TransferExists(transfer.region, transfer.serverId);
    }

    bool TransferMemoryDb::TransferExists(const std::string &serverId) {

        return find_if(_transfers.begin(),
                       _transfers.end(),
                       [serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                           return transfer.second.serverId == serverId;
                       }) != _transfers.end();
    }

    bool TransferMemoryDb::TransferExists(const std::string &region, const std::vector<std::string> &protocols) {

        return find_if(_transfers.begin(),
                       _transfers.end(),
                       [region, protocols](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                           return transfer.second.region == region && transfer.second.protocols == protocols;
                       }) != _transfers.end();
    }

    std::vector<Entity::Transfer::Transfer> TransferMemoryDb::ListServers(const std::string &region) {

        Entity::Transfer::TransferList transferList;
        if (region.empty()) {

            for (const auto &transfer: _transfers) {
                transferList.emplace_back(transfer.second);
            }

        } else {

            for (const auto &transfer: _transfers) {
                if (transfer.second.region == region) {
                    transferList.emplace_back(transfer.second);
                }
            }
        }

        log_trace << "Got transfer list, size: " << transferList.size();
        return transferList;
    }

    Entity::Transfer::Transfer TransferMemoryDb::CreateTransfer(const Entity::Transfer::Transfer &transfer) {
        Poco::ScopedLock lock(_transferMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _transfers[oid] = transfer;
        log_trace << "Transfer created, oid: " << oid;
        return GetTransferById(oid);
    }

    Entity::Transfer::Transfer TransferMemoryDb::UpdateTransfer(const Entity::Transfer::Transfer &transfer) {
        Poco::ScopedLock lock(_transferMutex);

        std::string region = transfer.region;
        std::string serverId = transfer.serverId;
        auto it = find_if(_transfers.begin(),
                          _transfers.end(),
                          [region, serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                              return transfer.second.region == region && transfer.second.serverId == serverId;
                          });

        if (it == _transfers.end()) {
            log_error << "Update transfer failed, serverId: " << serverId;
            throw Core::DatabaseException("Update transfer failed, serverId: " + serverId);
        }

        _transfers[it->first] = transfer;
        return _transfers[it->first];
    }

    Entity::Transfer::Transfer TransferMemoryDb::GetTransferById(const std::string &oid) {

        auto it = find_if(_transfers.begin(),
                          _transfers.end(),
                          [oid](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                              return transfer.first == oid;
                          });

        if (it == _transfers.end()) {
            log_error << "Get transfer by ID failed, oid: " << oid;
            throw Core::DatabaseException("Get transfer by ID failed, oid: " + oid);
        }

        it->second.oid = oid;
        return it->second;
    }

    Entity::Transfer::Transfer TransferMemoryDb::GetTransferByServerId(const std::string &serverId) {

        auto it = find_if(_transfers.begin(),
                          _transfers.end(),
                          [serverId](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                              return transfer.second.serverId == serverId;
                          });

        if (it == _transfers.end()) {
            log_error << "Get transfer by serverId failed, serverId: " << serverId;
            throw Core::DatabaseException("Get transfer by serverId failed, serverId: " + serverId);
        }

        it->second.oid = it->first;
        return it->second;
    }

    Entity::Transfer::Transfer TransferMemoryDb::GetTransferByArn(const std::string &arn) {

        auto it = find_if(_transfers.begin(),
                          _transfers.end(),
                          [arn](const std::pair<std::string, Entity::Transfer::Transfer> &transfer) {
                              return transfer.second.arn == arn;
                          });

        if (it == _transfers.end()) {
            log_error << "Get transfer by arn failed, arn: " << arn;
            throw Core::DatabaseException("Get transfer by arn failed, arn: " + arn);
        }

        it->second.oid = it->first;
        return it->second;
    }

    long TransferMemoryDb::CountServers(const std::string &region) {

        long count = 0;

        if (region.empty()) {

            count = (long) _transfers.size();

        } else {

            return std::count_if(std::begin(_transfers), std::end(_transfers),
                                 [region](std::pair<std::string, Entity::Transfer::Transfer> const &p) {
                                     return p.second.region == region;
                                 });
        }
        log_trace << "Count servers, result: " << count;
        return count;
    }


    void TransferMemoryDb::DeleteTransfer(const std::string &serverId) {
        Poco::ScopedLock lock(_transferMutex);

        const auto count = std::erase_if(_transfers, [serverId](const auto &item) {
            auto const &[key, value] = item;
            return value.serverId == serverId;
        });
        log_debug << "Transfer server deleted, count: " << count;
    }

    void TransferMemoryDb::DeleteAllTransfers() {
        Poco::ScopedLock lock(_transferMutex);

        log_debug << "All transfer servers deleted, count: " << _transfers.size();
        _transfers.clear();
    }
}// namespace AwsMock::Database