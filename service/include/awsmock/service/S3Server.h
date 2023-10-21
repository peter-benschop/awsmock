//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3SERVER_H
#define AWSMOCK_SERVICE_S3SERVER_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServer.h"

// AwsMock includes
#include "awsmock/core/LogStream.h"
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"
#include "awsmock/core/ThreadPool.h"
#include "awsmock/service/S3HandlerFactory.h"
#include "awsmock/service/S3Monitoring.h"

#define S3_DEFAULT_PORT 9500
#define S3_DEFAULT_HOST "localhost"

namespace AwsMock::Service {
  
  /**
   * S3 service
   */
  class S3Server : public Poco::Runnable, public AbstractWorker {
    
    public:
      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService monitoring service
       */
      explicit S3Server(Core::Configuration &configuration, Core::MetricService &metricService);
      
      /**
       * Destructor
       */
      ~S3Server();
      
      /**
       * Thread main method
       */
      void run();
    
    private:
      
      /**
       * Start the restfull service.
       */
      void StartHttpServer();
      
      /**
       * Start the monitoring service.
       */
      void StartMonitoringServer();
      
      /**
       * Update metric counters
       */
      void UpdateCounters();
      
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
       * Checks the existence of a bucket in the database, by sending the corresponding HeadObject request to the S3 service.
       *
       * @param bucket S3 bucket name
       * @return true if object exists
       */
      bool ExistsBucket(const std::string &bucket);
      
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
       * @param bucket bucket name
       * @param key object key
       * @retunr local file path
       */
      std::string GetFileFromBucketKey(const std::string &bucket, const std::string &key);
      
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
      void SendPutObjectRequest(const std::string &fileName, const std::string &bucket, const std::string &key, const std::string &md5Sum, const std::string &contentType, unsigned long fileSize);
      
      /**
       * Sends a head object request to the S3 service
       *
       * @param bucket S3 bucket name
       * @param contentType content type
       * @return true if object exists
       */
      bool SendHeadObjectRequest(const std::string &bucket, const std::string &contentType);
      
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
       * Rest port
       */
      int _port;
      
      /**
       * Rest host
       */
      std::string _host;
      
      /**
       * Logger
       */
      Core::LogStream _logger;
      
      /**
      * Application configuration
      */
      Core::Configuration &_configuration;
      
      /**
       * Metric service
       */
      Core::MetricService &_metricService;
      
      /**
       * HTTP server instance
       */
      Poco::Net::HTTPServer *_httpServer;
      
      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;
      
      /**
       * S3 database
       */
      std::unique_ptr<Database::S3Database> _s3Database;
      
      /**
       * HTTP max message queue length
       */
      int _maxQueueLength;
      
      /**
       * HTTP max concurrent connection
       */
      int _maxThreads;
      
      /**
       * Sleeping period in ms
       */
      int _period;
      
      /**
       * Running flag
       */
      bool _running;
      
      /**
       * Data directory
       */
      std::string _dataDir;
      
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
       * Thread pool
       */
      AwsMock::Core::ThreadPool<S3Monitoring> _threadPool;
      
      /**
       * S3 service host
       */
      std::string _s3ServiceHost;
      
      /**
       * S3 service port
       */
      int _s3ServicePort;
  };
  
} // namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_S3SERVER_H
