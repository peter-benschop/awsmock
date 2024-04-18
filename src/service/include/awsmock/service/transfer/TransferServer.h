//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFERSERVER_H
#define AWSMOCK_SERVICE_TRANSFERSERVER_H

// C++ standard includes
#include <string>
#include <map>
#include <memory>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/dto/s3/CreateBucketConstraint.h"
#include "awsmock/ftpserver/FtpServer.h"
#include "awsmock/repository/ModuleDatabase.h"
#include "awsmock/repository/TransferDatabase.h"
#include "awsmock/service/common/AbstractServer.h"
#include "awsmock/service/common/AbstractWorker.h"
#include "TransferHandlerFactory.h"

#define TRANSFER_DEFAULT_PORT 9504
#define TRANSFER_DEFAULT_HOST "localhost"
#define TRANSFER_DEFAULT_QUEUE_LENGTH  250
#define TRANSFER_DEFAULT_THREADS 50
#define TRANSFER_DEFAULT_TIMEOUT 120

#define DEFAULT_BASE_DIR "transfer"
#define CONTENT_TYPE_JSON "application/json"

namespace AwsMock::Service {

  class TransferServer : public AbstractServer, public AbstractWorker {

  public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring module
     */
    explicit TransferServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Initialization
     */
    void Initialize() override;

    /**
     * Main method
     */
    void Run() override;

    /**
     * Shutdown
     */
    void Shutdown() override;

  private:

    /**
     * Starts a single transfer manager
     *
     * @param server transfer manager entity
     */
    void StartTransferServer(Database::Entity::Transfer::Transfer &server);

    /**
     * Stops a single transfer manager
     *
     * @param server transfer manager entity
     */
    void StopTransferServer(Database::Entity::Transfer::Transfer &server);

    /**
     * Start all transfer servers, if they are not existing
     */
    void StartTransferServers();

    /**
     * Check transfer servers
     */
    void CheckTransferServers();

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * lambda database
     */
    Database::TransferDatabase& _transferDatabase;

    /**
     * Sleeping period in ms
     */
    int _period;

    /**
     * Rest port
     */
    int _port;

    /**
     * Rest host
     */
    std::string _host;

    /**
     * HTTP max message queue length
     */
    int _maxQueueLength;

    /**
     * HTTP max concurrent connection
     */
    int _maxThreads;

    /**
     * HTTP request timeout in seconds
     */
    int _requestTimeout;

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
     * S3 module host
     */
    std::string _s3ServiceHost;

    /**
     * S3 module port
     */
    int _s3ServicePort;

    /**
     * Module name
     */
    std::string _module;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_TRANSFERSERVER_H
