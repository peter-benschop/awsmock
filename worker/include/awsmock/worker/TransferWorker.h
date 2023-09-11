//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_WORKER_TRANSFERWORKER_H
#define AWSMOCK_WORKER_TRANSFERWORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/s3/CreateBucketConstraint.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/repository/TransferDatabase.h>
#include <awsmock/service/FtpServer.h>
#include <awsmock/worker/AbstractWorker.h>

#define DEFAULT_TRANSFER_BUCKET "transfer-server"
#define DEFAULT_BASE_DIR "transfer"
#define CONTENT_TYPE_JSON "application/json"

namespace AwsMock::Worker {

    class TransferWorker : public Poco::Runnable, public AbstractWorker {

    public:

      /**
       * Constructor
       */
      [[maybe_unused]] explicit TransferWorker(const Core::Configuration &configuration);

      /**
       * Main method
       */
      void run() override;

    private:

      /**
       * Starts a single transfer server
       *
       * @param server transfer server entity
       */
      void StartTransferServer(Database::Entity::Transfer::Transfer &server);

      /**
       * Stops a single transfer server
       *
       * @param server transfer server entity
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
       * @param bucket S3 bucket name
       */
      void SendCreateBucketRequest(const std::string &bucket);

      /**
       * Sends a create bucket request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param key S3 file key
       * @param fileName file to send
       */
      void SendCreateObjectRequest(const std::string &bucket, const std::string &key, const std::string &fileName);

      /**
       * Sends a delete bucket request to the S3 service
       *
       * @param bucket S3 bucket name
       */
      void SendDeleteBucketRequest(const std::string &bucket);

      /**
       * Sends a delete object request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param key S3 file key
       */
      void SendDeleteObjectRequest(const std::string &bucket, const std::string &key);

      /**
       * Sends a exists bucket request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param contentType content type
       * @return true when bucket exists
       */
      bool SendExistsBucketRequest(const std::string &bucket);

      /**
       * Callback for the directory watcher add events.
       *
       * <p>Actually, this is not used, as on Linux systems a added and afterwards a modified event is issued. We only use the modified event.</p>
       *
       * @param addEvent directory watcher add event.
       */
      void OnFileAdded(const Core::DirectoryEvent &addEvent);

      /**
       * Callback for the directory watcher change events.
       *
       * <p>Actually, this is used, for all create/modified events, as on Linux systems a added and afterwards a modified event is issued.</p>
       *
       * @param modifiedEvent directory watcher change event.
       */
      void OnFileModified(const Core::DirectoryEvent &modifiedEvent);

      /**
       * Callback for the directory watcher delete events.
       *
       * @param deleteEvent directory watcher delete event.
       */
      void OnFileDeleted(const Core::DirectoryEvent &deleteEvent);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;

      /**
       * Lambda database
       */
      std::unique_ptr<Database::TransferDatabase> _transferDatabase;

      /**
       * Directory _watcher thread
       */
      Poco::Thread _watcherThread;

      /**
       * Running flag
       */
      bool _running;

      /**
       * Sleeping period in ms
       */
      int _period;

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
       * List of transfer servers
       */
      std::map<std::string, std::shared_ptr<Service::FtpServer>> _transferServerList;

      /**
       * Directory _watcher
       */
      std::shared_ptr<Core::DirectoryWatcher> _watcher;

      /**
       * S3 service host
       */
      std::string _s3ServiceHost;

      /**
       * S3 service port
       */
      int _s3ServicePort;
    };

} // namespace AwsMock::Worker

#endif // AWSMOCK_WORKER_TRANSFERWORKER_H
