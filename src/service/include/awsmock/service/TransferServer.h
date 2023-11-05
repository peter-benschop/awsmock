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
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/s3/CreateBucketConstraint.h>
#include <awsmock/ftpserver/FtpServer.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/TransferDatabase.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/AbstractWorker.h>
#include <awsmock/service/TransferHandlerFactory.h>

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
     * @param metricService aws-mock monitoring service
     */
    explicit TransferServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~TransferServer() override;

    /**
     * Main method
     */
    void MainLoop() override;

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
     * Sends a create bucket request to the S3 service
     *
     * @param module AwsMock module name
     * @param bucket S3 bucket name
     */
    void SendCreateBucketRequest(const std::string &module, const std::string &bucket);

    /**
     * Sends a exists bucket request to the S3 service
     *
     * @param module AwsMock module name
     * @param bucket S3 bucket name
     * @return true when bucket exists
     */
    bool SendExistsBucketRequest(const std::string &module, const std::string &bucket);

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric service
     */
    Core::MetricService &_metricService;

    /**
     * Service database
     */
    std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

    /**
     * lambda database
     */
    std::unique_ptr<Database::TransferDatabase> _transferDatabase;

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
     * Server id
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
     * S3 service host
     */
    std::string _s3ServiceHost;

    /**
     * S3 service port
     */
    int _s3ServicePort;

    /**
     * Module name
     */
    std::string _module;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_TRANSFERSERVER_H
