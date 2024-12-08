//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_SERVICE_H
#define AWSMOCK_SERVICE_TRANSFER_SERVICE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/transfer/CreateServerRequest.h>
#include <awsmock/dto/transfer/CreateServerResponse.h>
#include <awsmock/dto/transfer/CreateUserRequest.h>
#include <awsmock/dto/transfer/CreateUserResponse.h>
#include <awsmock/dto/transfer/DeleteServerRequest.h>
#include <awsmock/dto/transfer/ListServerRequest.h>
#include <awsmock/dto/transfer/ListServerResponse.h>
#include <awsmock/dto/transfer/ListUsersRequest.h>
#include <awsmock/dto/transfer/ListUsersResponse.h>
#include <awsmock/dto/transfer/StartServerRequest.h>
#include <awsmock/dto/transfer/StopServerRequest.h>
#include <awsmock/dto/transfer/mapper/Mapper.h>
#include <awsmock/repository/TransferDatabase.h>
#include <awsmock/service/monitoring/MetricDefinition.h>
#include <awsmock/service/monitoring/MetricServiceTimer.h>

#define TRANSFER_DEFAULT_FTP_PORT 21

namespace AwsMock::Service {

    /**
     * @brief Transfer family service
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TransferService {

      public:

        /**
         * @brief Constructor
         */
        explicit TransferService() : _transferDatabase(Database::TransferDatabase::instance()) {};

        /**
         * @brief Create transfer server request
         *
         * @param request create server request
         * @return CreateServerResponse
         * @see Dto::Transfer::CreateServerResponse
         */
        Dto::Transfer::CreateServerResponse CreateTransferServer(Dto::Transfer::CreateServerRequest &request) const;

        /**
         * @brief Create a user for the transfer manager.
         *
         * @param request create user request
         * @return CreateUserResponse
         * @see Dto::Transfer::CreateUserResponse
         */
        Dto::Transfer::CreateUserResponse CreateUser(Dto::Transfer::CreateUserRequest &request) const;

        /**
         * @brief Returns a list of available servers
         *
         * @param request list manager request
         * @return ListServerResponse
         * @see Dto::Transfer::ListServerResponse
         */
        Dto::Transfer::ListServerResponse ListServers(const Dto::Transfer::ListServerRequest &request) const;

        /**
         * @brief Returns a list of available servers
         *
         * @param request list manager request
         * @return ListServerResponse
         * @see Dto::Transfer::ListServerResponse
         */
        Dto::Transfer::ListUsersResponse ListUsers(const Dto::Transfer::ListUsersRequest &request) const;

        /**
         * @brief Starts a manager.
         *
         * @param request StartServer manager request
         */
        void StartServer(const Dto::Transfer::StartServerRequest &request) const;

        /**
         * @brief Stops a manager.
         *
         * @param request stop manager request
         */
        void StopServer(const Dto::Transfer::StopServerRequest &request) const;

        /**
         * @brief Deleted a manager.
         *
         * @param request delete manager request
         */
        void DeleteServer(const Dto::Transfer::DeleteServerRequest &request) const;

      private:

        /**
         * Transfer database connection
         */
        Database::TransferDatabase &_transferDatabase;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_SERVICE_H
