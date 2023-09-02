//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/TransferDatabase.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    TransferDatabase::TransferDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("TransferDatabase")) {

        // Get collection
        _transferCollection = GetConnection()["transfer"];
    }

    bool TransferDatabase::TransferExists(const std::string &region, const std::string &serverId) {

        int64_t count = _transferCollection.count_documents(make_document(kvp("region", region), kvp("serverId", serverId)));
        log_trace_stream(_logger) << "Transfer server exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
    }

    bool TransferDatabase::TransferExists(const Entity::Transfer::Transfer &transfer) {

        return TransferExists(transfer.region, transfer.serverId);
    }

    bool TransferDatabase::TransferExists(const std::string &serverId) {

        int64_t count = _transferCollection.count_documents(make_document(kvp("serverId", serverId)));
        log_trace_stream(_logger) << "Transfer server exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
    }

    bool TransferDatabase::TransferExists(const std::string &region, std::vector<std::string> protocols) {

        bsoncxx::builder::basic::array mProtocol{};
        for (const auto &p : protocols) {
            mProtocol.append(p);
        }

        int64_t count = _transferCollection.count_documents(make_document(kvp("region", region),
                                                                          kvp("protocols",
                                                                              make_document(kvp("$in", mProtocol)))));
        log_trace_stream(_logger) << "Transfer server exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
    }

    Entity::Transfer::Transfer TransferDatabase::CreateTransfer(const Entity::Transfer::Transfer &transfer) {

        auto result = _transferCollection.insert_one(transfer.ToDocument());
        log_trace_stream(_logger) << "Bucket created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

        return GetTransferById(result->inserted_id().get_oid().value);
    }

    Entity::Transfer::Transfer TransferDatabase::GetTransferById(bsoncxx::oid oid) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _transferCollection.find_one(make_document(kvp("_id", oid)));
        Entity::Transfer::Transfer result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::Transfer::Transfer TransferDatabase::GetTransferById(const std::string &oid) {
        return GetTransferById(bsoncxx::oid(oid));
    }

    Entity::Transfer::Transfer TransferDatabase::GetTransferByServerId(const std::string &serverId) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _transferCollection.find_one(make_document(kvp("serverId", serverId)));
        Entity::Transfer::Transfer result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::Transfer::Transfer TransferDatabase::CreateOrUpdateTransfer(const Entity::Transfer::Transfer &lambda) {

        if (TransferExists(lambda)) {
            return UpdateTransfer(lambda);
        } else {
            return CreateTransfer(lambda);
        }
    }

    Entity::Transfer::Transfer TransferDatabase::UpdateTransfer(const Entity::Transfer::Transfer &transfer) {

        auto result = _transferCollection.replace_one(make_document(kvp("region", transfer.region), kvp("serverId", transfer.serverId)),
                                                      transfer.ToDocument());

        log_trace_stream(_logger) << "Transfer updated: " << transfer.ToString() << std::endl;

        return GetTransferByServerId(transfer.serverId);
    }

    Entity::Transfer::Transfer TransferDatabase::GetTransferByArn(const std::string &arn) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _transferCollection.find_one(make_document(kvp("arn", arn)));
        Entity::Transfer::Transfer result;
        result.FromDocument(mResult);

        return result;
    }

    std::vector<Entity::Transfer::Transfer> TransferDatabase::ListServers(const std::string &region) {

        std::vector<Entity::Transfer::Transfer> transfers;
        auto transferCursor = _transferCollection.find(make_document(kvp("region", region)));
        for (auto transfer : transferCursor) {
            Entity::Transfer::Transfer result;
            result.FromDocument(transfer);
            transfers.push_back(result);
        }
        log_trace_stream(_logger) << "Got transfer list, size:" << transfers.size() << std::endl;

        return transfers;
    }

    void TransferDatabase::DeleteTransfer(const std::string &serverId) {

        auto result = _transferCollection.delete_many(make_document(kvp("serverId", serverId)));
        log_debug_stream(_logger) << "Transfer deleted, serverId: " << serverId << " count: " << result->deleted_count() << std::endl;
    }

    void TransferDatabase::DeleteAllTransfers() {
        auto result = _transferCollection.delete_many({});
        log_debug_stream(_logger) << "All transfers deleted, count: " << result->deleted_count() << std::endl;
    }

} // namespace AwsMock::Database
