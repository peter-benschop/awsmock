//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/transfer/TransferService.h>

namespace AwsMock::Service {

    Dto::Transfer::CreateServerResponse TransferService::CreateTransferServer(Dto::Transfer::CreateServerRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "create_transfer_server");
        log_debug << "Create transfer manager";

        // Check existence
        if (_transferDatabase.TransferExists(request.region, request.protocols)) {
            log_error << "Transfer manager exists already";
            throw Core::ServiceException("Transfer manager exists already");
        }

        std::string serverId = "s-" + Poco::toLower(Core::StringUtils::GenerateRandomHexString(20));

        Database::Entity::Transfer::Transfer transferEntity;
        std::string accountId = Core::Configuration::instance().GetValueString("awsmock.access.account-id");
        std::string transferArn = Core::AwsUtils::CreateTransferArn(request.region, accountId, serverId);
        std::string listenAddress = Core::Configuration::instance().GetValueString("awsmock.modules.transfer.ftp.address");

        // Create entity
        int ftpPort = Core::Configuration::instance().GetValueInt("awsmock.modules.transfer.ftp.port");
        transferEntity = {.region = request.region, .serverId = serverId, .arn = transferArn, .protocols = request.protocols, .port = ftpPort, .listenAddress = listenAddress};

        // Add anonymous user
        Database::Entity::Transfer::User anonymousUser = {.userName = "anonymous", .password = "secret", .homeDirectory = "/"};
        transferEntity.users.emplace_back(anonymousUser);

        transferEntity = _transferDatabase.CreateTransfer(transferEntity);

        // Create response
        Dto::Transfer::CreateServerResponse response{.region = transferEntity.region, .serverId = serverId, .arn = transferArn};

        return response;
    }

    Dto::Transfer::CreateUserResponse TransferService::CreateUser(Dto::Transfer::CreateUserRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "create_user_server");
        log_debug << "Create user request";

        Database::Entity::Transfer::Transfer transferEntity;

        if (!_transferDatabase.TransferExists(request.region, request.serverId)) {

            throw Core::ServiceException("Transfer manager with ID '" + request.serverId + "  does not exist");
        }
        transferEntity = _transferDatabase.GetTransferByServerId(request.serverId);

        // Check user
        if (transferEntity.HasUser(request.userName)) {
            log_warning << "Transfer manager has already a user with name '" + request.userName + "'";
            Database::Entity::Transfer::User user = transferEntity.GetUser(request.userName);
            return {.region = transferEntity.region, .serverId = transferEntity.serverId, .userName = user.userName};
        }

        // Get home directory
        std::string homeDirectory = request.userName;
        if (!Core::StringUtils::IsNullOrEmpty(&request.homeDirectory)) {
            homeDirectory = request.homeDirectory;
        }

        // Add user
        std::string accountId = Core::Configuration::instance().GetValueString("awsmock.access.account-id");
        std::string userArn = Core::AwsUtils::CreateTransferUserArn(request.region, accountId, transferEntity.serverId, request.userName);
        Database::Entity::Transfer::User user = {
                .userName = request.userName,
                .password = Core::StringUtils::GenerateRandomPassword(8),
                .homeDirectory = homeDirectory,
                .arn = userArn};
        transferEntity.users.emplace_back(user);

        // Update database
        transferEntity = _transferDatabase.UpdateTransfer(transferEntity);
        log_debug << "Updated transfer manager, serverId: " << transferEntity.serverId;

        // Create response
        Dto::Transfer::CreateUserResponse response{.region = transferEntity.region, .serverId = transferEntity.serverId, .userName = request.userName};

        return response;
    }

    Dto::Transfer::ListServerResponse TransferService::ListServers(const Dto::Transfer::ListServerRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "list_servers");

        try {
            std::vector<Database::Entity::Transfer::Transfer> servers = _transferDatabase.ListServers(request.region);

            auto response = Dto::Transfer::ListServerResponse();
            response.nextToken = Core::StringUtils::CreateRandomUuid();
            for (const auto &s: servers) {
                Dto::Transfer::Server server = {
                        .arn = s.arn,
                        .serverId = s.serverId,
                        .state = ServerStateToString(s.state),
                        .userCount = static_cast<int>(s.users.size())};
                response.servers.emplace_back(server);
            }

            log_trace << "Handler list outcome: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Handler list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::Transfer::ListUsersResponse TransferService::ListUsers(const Dto::Transfer::ListUsersRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "list_users");

        try {
            const std::vector<Database::Entity::Transfer::User> users = _transferDatabase.ListUsers(request.region, request.serverId);

            Dto::Transfer::ListUsersResponse response = Dto::Transfer::Mapper::map(request, users);
            response.nextToken = Core::StringUtils::CreateRandomUuid();

            log_trace << "Handler list outcome: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Handler list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void TransferService::StartServer(const Dto::Transfer::StartServerRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "start_server");

        Database::Entity::Transfer::Transfer server;
        try {
            if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
                log_error << "Handler with ID '" << request.serverId << "' does not exist";
                throw Core::ServiceException("Handler with ID '" + request.serverId + "' does not exist");
            }

            // Get the manager
            server = _transferDatabase.GetTransferByServerId(request.serverId);

            // Update state, rest will be done by transfer worker
            server.state = Database::Entity::Transfer::ServerState::ONLINE;
            server = _transferDatabase.UpdateTransfer(server);
            log_info << "Transfer server started, serverId: " << server.serverId;

        } catch (Poco::Exception &ex) {

            // Update state
            server.state = Database::Entity::Transfer::ServerState::START_FAILED;
            server = _transferDatabase.UpdateTransfer(server);

            log_error << "Start transfer server request failed, serverId: " << server.serverId << " message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void TransferService::StopServer(const Dto::Transfer::StopServerRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "stop_server");

        Database::Entity::Transfer::Transfer server;
        try {
            if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
                throw Core::ServiceException("Handler with ID '" + request.serverId + "' does not exist");
            }

            // Get the manager
            server = _transferDatabase.GetTransferByServerId(request.serverId);

            // Update state, rest will be done by transfer worker
            server.state = Database::Entity::Transfer::ServerState::OFFLINE;
            server = _transferDatabase.UpdateTransfer(server);
            log_info << "Transfer manager stopped, serverId: " << server.serverId;

        } catch (Poco::Exception &ex) {

            // Update state
            server.state = Database::Entity::Transfer::ServerState::STOP_FAILED;
            server = _transferDatabase.UpdateTransfer(server);

            log_error << "Stop manager request failed, serverId: " << server.serverId << " message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void TransferService::DeleteServer(const Dto::Transfer::DeleteServerRequest &request) const {
        Monitoring::MetricServiceTimer measure(TRANSFER_SERVICE_TIMER, "method", "delete_server");

        Database::Entity::Transfer::Transfer server;
        try {
            if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
                log_error << "Handler with ID '" + request.serverId + "' does not exist";
                throw Core::ServiceException("Handler with ID '" + request.serverId + "' does not exist");
            }

            // Get the manager
            server = _transferDatabase.GetTransferByServerId(request.serverId);

            // Update state, rest will be done by transfer worker
            server.state = Database::Entity::Transfer::ServerState::OFFLINE;
            server = _transferDatabase.UpdateTransfer(server);
            log_info << "Transfer manager stopped, serverId: " << server.serverId;

            _transferDatabase.DeleteTransfer(request.serverId);
            log_info << "Transfer manager deleted, serverId: " << server.serverId;

        } catch (Poco::Exception &ex) {

            // Update state
            server.state = Database::Entity::Transfer::ServerState::STOP_FAILED;
            server = _transferDatabase.UpdateTransfer(server);

            log_error << "Start manager request failed, serverId: " << server.serverId << " message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }
}// namespace AwsMock::Service
