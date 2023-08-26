//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/TransferService.h>

namespace AwsMock::Service {

    TransferService::TransferService(const Core::Configuration &configuration) : _logger("TransferService"), _configuration(configuration) {
        Initialize();
    }

    void TransferService::Initialize() {

        // Initialize environment
        _accountId = _configuration.getString("awsmock.account.id", "000000000000");
        _transferDatabase = std::make_unique<Database::TransferDatabase>(_configuration);
        log_debug_stream(_logger) << "Transfer service initialized" << std::endl;
    }

    Dto::Transfer::CreateTransferResponse
    TransferService::CreateTransferServer(Dto::Transfer::CreateTransferRequest &request) {
        log_debug_stream(_logger) << "Create transfer server" << std::endl;

        std::string serverId = "s-" + Poco::toLower(Core::StringUtils::GenerateRandomHexString(20));

        Database::Entity::Transfer::Transfer transferEntity;
        std::string transferArn = Core::AwsUtils::CreateTransferArn(request.region, _accountId, serverId);

        if (_transferDatabase->TransferExists(request.region, serverId)) {

            transferEntity = _transferDatabase->GetTransferByArn(transferArn);

        } else {

            // Create entity
            transferEntity = {.region=request.region, .serverId=serverId, .arn=transferArn, .protocols=request.protocols};

            // Add anonymous user
            Database::Entity::Transfer::User anonymousUser = {.userName="anonymous", .password="123", .homeDirectory="/"};
            transferEntity.users.emplace_back(anonymousUser);

            transferEntity = _transferDatabase->CreateTransfer(transferEntity);

        }

        // Create response
        Dto::Transfer::CreateTransferResponse
            response{.region=transferEntity.region, .serverId=serverId, .arn=transferArn};

        return response;
    }

    Dto::Transfer::CreateUserResponse
    TransferService::CreateUser(Dto::Transfer::CreateUserRequest &request) {
        log_debug_stream(_logger) << "Create user request" << std::endl;

        Database::Entity::Transfer::Transfer transferEntity;

        if (!_transferDatabase->TransferExists(request.region, request.serverId)) {

            throw Core::ServiceException("Transfer server with ID '" + request.serverId + "  does not exist", 500);

        } else {

            transferEntity = _transferDatabase->GetTransferByServerId(request.serverId);

            // Check user
            if (transferEntity.HasUser(request.userName)) {
                throw Core::ServiceException("Transfer server has already a user with name '" + request.userName + "'", 500);
            }

            // Get home directory
            std::string homeDirectory = request.userName;
            if(!Core::StringUtils::IsNullOrEmpty(&request.homeDirectory)) {
                homeDirectory = request.homeDirectory;
            }

            // Add user
            Database::Entity::Transfer::User
                user = {.userName=request.userName, .password=Core::StringUtils::GenerateRandomPassword(8), .homeDirectory=request.homeDirectory};
            transferEntity.users.emplace_back(user);

            // Update database
            transferEntity = _transferDatabase->UpdateTransfer(transferEntity);
            log_debug_stream(_logger) << "Updated transfer server, serverId: " << transferEntity.serverId << std::endl;
        }

        // Create response
        Dto::Transfer::CreateUserResponse response{.region=transferEntity.region, .serverId=transferEntity.serverId, .userName=request.userName};

        return response;
    }
} // namespace AwsMock::Service
