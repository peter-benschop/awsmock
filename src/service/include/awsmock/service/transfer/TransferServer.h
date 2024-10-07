//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_SERVER_H
#define AWSMOCK_SERVICE_TRANSFER_SERVER_H

// C++ standard includes
#include <map>
#include <memory>
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/dto/s3/CreateBucketConstraint.h>
#include <awsmock/ftpserver/FtpServer.h>
#include <awsmock/repository/TransferDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/transfer/TransferMonitoring.h>

#define TRANSFER_DEFAULT_MONITORING_PERIOD 300
#define DEFAULT_BASE_DIR "transfer"

namespace AwsMock::Service {

    /**
     * @brief Transfer server HTTP server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TransferServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit TransferServer();

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * @brief Creates the transfer server bucket
         */
        static void CreateTransferBucket();

        /**
         * @brief Starts a single transfer manager
         *
         * @param server transfer manager entity
         */
        void StartTransferServer(Database::Entity::Transfer::Transfer &server);

        /**
         * @brief Stops a single transfer manager
         *
         * @param server transfer manager entity
         */
        void StopTransferServer(Database::Entity::Transfer::Transfer &server);

        /**
         * @brief Start all transfer servers, if they are not existing
         */
        void StartTransferServers();

        /**
         * @brief Check transfer servers
         */
        void CheckTransferServers();

        /**
         * Transfer database
         */
        Database::TransferDatabase &_transferDatabase;

        /**
         * Transfer monitoring
         */
        TransferMonitoring _transferMonitoring;

        /**
         * AWS region
         */
        std::string _region;

        /**
         * AWS client ID
         */
        std::string _clientId;

        /**
         * AWS user
         */
        std::string _user;

        /**
         * AWS S3 bucket
         */
        std::string _bucket;

        /**
         * Base dir for all FTP users
         */
        std::string _baseDir;

        /**
         * Base URL for all S3 request
         */
        std::string _baseUrl;

        /**
         * Server userPoolId
         */
        std::string _serverId;

        /**
         * List of transfer servers
         */
        std::map<std::string, std::shared_ptr<FtpServer::FtpServer>> _transferServerList;

        /**
         * Actual FTP manager
         */
        std::shared_ptr<FtpServer::FtpServer> _ftpServer;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_SERVER_H
