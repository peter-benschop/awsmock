//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFERSERVICE_H
#define AWSMOCK_SERVICE_TRANSFERSERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/RecursiveDirectoryIterator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/db/TransferDatabase.h>
#include <awsmock/dto/transfer/CreateTransferRequest.h>
#include <awsmock/dto/transfer/CreateTransferResponse.h>
#include <awsmock/dto/transfer/CreateUserRequest.h>
#include <awsmock/dto/transfer/CreateUserResponse.h>
#include <awsmock/dto/transfer/DeleteServerRequest.h>
#include <awsmock/dto/transfer/ListServerRequest.h>
#include <awsmock/dto/transfer/ListServerResponse.h>
#include <awsmock/dto/transfer/StartServerRequest.h>
#include <awsmock/dto/transfer/StopServerRequest.h>
#include <awsmock/service/FtpServer.h>

namespace AwsMock::Service {

    class TransferService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit TransferService(const Core::Configuration &configuration);

      /**
       * Create transfer server request
       *
       * @param request create transfer request
       * @return CreateTransferResponse
       */
      Dto::Transfer::CreateTransferResponse CreateTransferServer(Dto::Transfer::CreateTransferRequest &request);

      /**
       * Create a user for the transfer server.
       *
       * @param request create user request
       * @return CreateUserResponse
       */
      Dto::Transfer::CreateUserResponse CreateUser(Dto::Transfer::CreateUserRequest &request);

      /**
       * Returns a list of available servers
       *
       * @param request list server request
       * @return ListServerResponse
       */
      Dto::Transfer::ListServerResponse ListServers(const Dto::Transfer::ListServerRequest &request);

      /**
       * Starts an server.
       *
       * @param request start server request
       */
      void StartServer(const Dto::Transfer::StartServerRequest &request);

      /**
       * Stops an server.
       *
       * @param request stop server request
       */
      void StopServer(const Dto::Transfer::StopServerRequest &request);

      /**
       * Deleted an server.
       *
       * @param request delete server request
       */
      void DeleteServer(const Dto::Transfer::DeleteServerRequest &request);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * Create a new transfer server instance.
       *
       * @param transferEntity transfer database entity
       */
      void CreateTransferServer(Database::Entity::Transfer::Transfer transferEntity);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * AWS account ID
       */
      std::string _accountId;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Transfer database connection
       */
      std::unique_ptr<Database::TransferDatabase> _transferDatabase;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_TRANSFERSERVICE_H
