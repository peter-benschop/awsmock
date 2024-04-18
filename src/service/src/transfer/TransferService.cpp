//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/transfer/TransferService.h>

namespace AwsMock::Service {

  TransferService::TransferService(Core::Configuration &configuration) : _configuration(configuration),_transferDatabase(Database::TransferDatabase::instance()) {

    // Initialize environment
    _ftpPort = _configuration.getInt("awsmock.module.transfer.ftp.port", TRANSFER_DEFAULT_FTP_PORT);
    _accountId = _configuration.getString("awsmock.account.userPoolId", "000000000000");

    log_trace << "Transfer module initialized";
  }

  Dto::Transfer::CreateServerResponse
  TransferService::CreateTransferServer(Dto::Transfer::CreateServerRequest &request) {

    log_debug << "Create transfer manager";

    // Check existence
    if (_transferDatabase.TransferExists(request.region, request.protocols)) {
      throw Core::ServiceException("Transfer manager exists already", 403);
    }

    std::string serverId = "s-" + Poco::toLower(Core::StringUtils::GenerateRandomHexString(20));

    Database::Entity::Transfer::Transfer transferEntity;
    std::string transferArn = Core::AwsUtils::CreateTransferArn(request.region, _accountId, serverId);

    // Create entity
    transferEntity = {.region=request.region, .serverId=serverId, .arn=transferArn, .protocols=request.protocols, .port=_ftpPort};

    // Add anonymous user
    Database::Entity::Transfer::User anonymousUser = {.userName="anonymous", .password="123", .homeDirectory="/"};
    transferEntity.users.emplace_back(anonymousUser);

    transferEntity = _transferDatabase.CreateTransfer(transferEntity);

    // Create response
    Dto::Transfer::CreateServerResponse
        response{.region=transferEntity.region, .serverId=serverId, .arn=transferArn};

    return response;
  }

  Dto::Transfer::CreateUserResponse
  TransferService::CreateUser(Dto::Transfer::CreateUserRequest &request) {
    log_debug << "Create user request";

    Database::Entity::Transfer::Transfer transferEntity;

    if (!_transferDatabase.TransferExists(request.region, request.serverId)) {

      throw Core::ServiceException("Transfer manager with ID '" + request.serverId + "  does not exist", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

    } else {

      transferEntity = _transferDatabase.GetTransferByServerId(request.serverId);

      // Check user
      if (transferEntity.HasUser(request.userName)) {
        throw Core::ServiceException("Transfer manager has already a user with name '" + request.userName + "'", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
      }

      // Get home directory
      std::string homeDirectory = request.userName;
      if (!Core::StringUtils::IsNullOrEmpty(&request.homeDirectory)) {
        homeDirectory = request.homeDirectory;
      }

      // Add user
      Database::Entity::Transfer::User
          user = {
          .userName=request.userName,
          .password=Core::StringUtils::GenerateRandomPassword(8),
          .homeDirectory=request.homeDirectory
      };
      transferEntity.users.emplace_back(user);

      // Update database
      transferEntity = _transferDatabase.UpdateTransfer(transferEntity);
      log_debug << "Updated transfer manager, serverId: " << transferEntity.serverId;
    }

    // Create response
    Dto::Transfer::CreateUserResponse response{.region=transferEntity.region, .serverId=transferEntity.serverId, .userName=request.userName};

    return response;
  }

  Dto::Transfer::ListServerResponse TransferService::ListServers(const Dto::Transfer::ListServerRequest &request) {

    try {
      std::vector<Database::Entity::Transfer::Transfer> servers = _transferDatabase.ListServers(request.region);

      auto response = Dto::Transfer::ListServerResponse();
      response.nextToken = Poco::UUIDGenerator().createRandom().toString();
      for (const auto &s : servers) {
        Dto::Transfer::Server server = {
            .arn=s.arn,
            .serverId=s.serverId,
            .state=s.state,
            .userCount=static_cast<int>(s.users.size())};
        response.servers.emplace_back(server);
      }

      log_trace << "Server list outcome: " + response.ToJson();
      return response;

    } catch (Poco::Exception &ex) {
      log_error << "Server list request failed, message: " << ex.message();
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void TransferService::StartServer(const Dto::Transfer::StartServerRequest &request) {

    Database::Entity::Transfer::Transfer server;
    try {
      if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
        throw Core::ServiceException("Server with ID '" + request.serverId + "' does not exist", 500);
      }

      // Get the manager
      server = _transferDatabase.GetTransferByServerId(request.serverId);

      // Update state, rest will be done by transfer worker
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE);
      server = _transferDatabase.UpdateTransfer(server);
      log_info << "Transfer manager started, serverId: " << server.serverId;

    } catch (Poco::Exception &ex) {

      // Update state
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::START_FAILED);
      server = _transferDatabase.UpdateTransfer(server);

      log_error << "Start manager request failed, serverId: " << server.serverId << " message: " << ex.message();
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void TransferService::StopServer(const Dto::Transfer::StopServerRequest &request) {

    Database::Entity::Transfer::Transfer server;
    try {
      if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
        throw Core::ServiceException("Server with ID '" + request.serverId + "' does not exist", 500);
      }

      // Get the manager
      server = _transferDatabase.GetTransferByServerId(request.serverId);

      // Update state, rest will be done by transfer worker
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);
      server = _transferDatabase.UpdateTransfer(server);
      log_info << "Transfer manager stopped, serverId: " << server.serverId;

    } catch (Poco::Exception &ex) {

      // Update state
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::STOP_FAILED);
      server = _transferDatabase.UpdateTransfer(server);

      log_error << "Stop manager request failed, serverId: " << server.serverId << " message: " << ex.message();
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void TransferService::DeleteServer(const Dto::Transfer::DeleteServerRequest &request) {

    Database::Entity::Transfer::Transfer server;
    try {
      if (!_transferDatabase.TransferExists(request.region, request.serverId)) {
        throw Core::ServiceException("Server with ID '" + request.serverId + "' does not exist", 500);
      }

      // Get the manager
      server = _transferDatabase.GetTransferByServerId(request.serverId);

      // Update state, rest will be done by transfer worker
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);
      server = _transferDatabase.UpdateTransfer(server);
      log_info << "Transfer manager stopped, serverId: " << server.serverId;

      _transferDatabase.DeleteTransfer(request.serverId);
      log_info << "Transfer manager deleted, serverId: " << server.serverId;

    } catch (Poco::Exception &ex) {

      // Update state
      server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::STOP_FAILED);
      server = _transferDatabase.UpdateTransfer(server);

      log_error << "Start manager request failed, serverId: " << server.serverId << " message: " << ex.message();
      throw Core::ServiceException(ex.message(), 500);
    }
  }
} // namespace AwsMock::Service
