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

        std::string serverId = "s-" + Poco::toLower(Core::StringUtils::GenerateRandomString(16));

        Database::Entity::Transfer::Transfer transferEntity;
        std::string transferArn = Core::AwsUtils::CreateTransferArn(request.region, _accountId, serverId);

        if (_transferDatabase->TransferExists(request.region, serverId)) {

            transferEntity = _transferDatabase->GetTransferByArn(transferArn);

        } else {

            transferEntity = {.region=request.region, .name=serverId, .arn=transferArn};
            transferEntity = _transferDatabase->CreateTransfer(transferEntity);

        }

        // Create response
        Dto::Transfer::CreateTransferResponse
            response{.region=transferEntity.region, .serverId=serverId, .arn=transferArn};

        return response;
    }

/*    void TransferService::CreateTransferServer(Database::Entity::Transfer::Transfer transferEntity){

        // Set transfer server parameter
        std::shared_ptr<FtpServer> ftpServer = std::make_shared<FtpServer>(_configuration);
        Poco::ThreadPool::defaultPool().start(*ftpServer);

        log_info_stream(_logger) << "FTP transfer server started" << std::endl;
    }*/
} // namespace AwsMock::Service
