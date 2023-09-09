//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_WORKER_S3WORKER_H
#define AWSMOCK_WORKER_S3WORKER_H

// C++ standard includes
#include <string>
#include <iostream>
#include <sys/inotify.h>

// Poco includes
#include "Poco/Delegate.h"
#include <Poco/DirectoryWatcher.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/Runnable.h>
#include <Poco/ScopedLock.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/DirectoryWatcher.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/dto/s3/CreateBucketConstraint.h>
#include <awsmock/dto/s3/PutObjectRequest.h>
#include <awsmock/worker/AbstractWorker.h>

namespace AwsMock::Worker {

    class S3Worker : public Poco::Runnable, public AbstractWorker {

    public:

      /**
       * Constructor
       */
      explicit S3Worker(const Core::Configuration &configuration);

      /**
       * Destructor
       */
      ~S3Worker() override;

      /**
       * Main method
       */
      void run() override;

    private:

      /**
       * Initialization
       */
      void Initialize();

      /**
       * Synchronize the directory layout with the database.
       * <p>
       * All files which are in the directory tree will be syncheonized with the database. Files not existing anymore on the file system, will be deleted from the
       * S3Object collection.
       * </p>
       */
      void Synchronize();

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
       * Create a new bucket, by sending the corresponding CreateBucket request to the S3 service.
       *
       * @param dirPath absolute path of the directory
       */
      void CreateBucket(const std::string &dirPath);

      /**
       * Deletes an existing bucket, by sending the corresponding DeleteBucket request to the S3 service.
       *
       * @param dirPath absolute path of the directory
       */
      void DeleteBucket(const std::string &dirPath);

      /**
       * Create a new object, by sending the corresponding PutObject request to the S3 service.
       *
       * @param filePath absolute path of the file
       */
      void CreateObject(const std::string &filePath);

      /**
       * Checks the existence of an object in database, by sending the corresponding HeadObject request to the S3 service.
       *
       * @param bucket S3 bucket name
       * @param key S3 object key
       * @return true if object exists
       */
      bool ExistsObject(const std::string &bucket, const std::string &key);

      /**
       * Deletes an existing object, by sending the corresponding DeleteObject request to the S3 service.
       *
       * @param bucket S3 bucket name
       * @param key S3 object key
       */
      void DeleteObject(const std::string &bucket, const std::string &key);

      /**
       * Gets the bucket and object key from the file name.
       *
       * @param fileName absolute file file name
       * @param bucket bucket name
       * @param key object key
       */
      void GetBucketKeyFromFile(const std::string &fileName, std::string &bucket, std::string &key);

      /**
       * Gets the absolute file path from bucket and object key.
       *
       * @param fileName absolute file file name
       * @param bucket bucket name
       * @param key object key
       */
      void GetFileFromBucketKey(std::string &fileName, const std::string &bucket, const std::string &key);

      /**
       * Sends a create object request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param contentType content type
       */
      void SendCreateBucketRequest(const std::string &bucket, const std::string &contentType);

      /**
       * Sends a delete bucket request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param contentType content type
       */
      void SendDeleteBucketRequest(const std::string &bucket, const std::string &contentType);

      /**
       * Sends a put object request to the S3 service
       *
       * @param fileName name of the file
       * @param bucket S3 bucket name
       * @param key S3 object key
       * @param md5Sum MD5 hash
       * @param contentType content type
       * @param fileSize size of the file
       */
      void SendPutObjectRequest(const std::string &fileName,
                                const std::string &bucket,
                                const std::string &key,
                                const std::string &md5Sum,
                                const std::string &contentType,
                                unsigned long fileSize);

      /**
       * Sends a head object request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param key S3 object key
       * @param contentType content type
       * @return true if object exists
       */
      bool SendHeadObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType);

      /**
       * Sends a delete object request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param key S3 object key
       * @param contentType content type
       */
      void SendDeleteObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType);

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
       * S3 database
       */
      std::unique_ptr<Database::S3Database> _s3Database;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Watcher directory
       */
      std::string _watcherDir;

      /**
       * Temp directory
       */
      std::string _tmpDir;

      /**
       * Directory _watcher thread
       */
      Poco::Thread _watcherThread;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * AWS account ID
       */
      std::string _accountId;

      /**
       * AWS client ID
       */
      std::string _clientId;

      /**
       * AWS user
       */
      std::string _user;

      /**
       * Directory _watcher
       */
      Core::DirectoryWatcher *_watcher;

      /**
       * Running flag
       */
      bool _running;

      /**
       * Sleeping period in ms
       */
      int _period;

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

#endif //AWSMOCK_WORKER_S3WORKER_H
