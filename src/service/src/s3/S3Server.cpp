//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server(boost::asio::thread_pool &pool) : AbstractServer("s3"), _module("s3"), _pool(pool) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.s3.http.port", S3_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.s3.http.host", S3_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.s3.http.max.queue", S3_DEFAULT_QUEUE_SIZE);
        _maxThreads = configuration.getInt("awsmock.service.s3.http.max.threads", S3_DEFAULT_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.s3.http.timeout", S3_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.s3.monitoring.period", S3_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.s3.worker.period", S3_DEFAULT_WORKER_PERIOD);

        // Monitoring
        _s3Monitoring = std::make_shared<S3Monitoring>(_monitoringPeriod);

        // Worker thread
        _s3Worker = std::make_shared<S3Worker>(_workerPeriod);

        log_debug << "S3 module initialized, endpoint: " << _host << ":" << _port;
    }

    void S3Server::Initialize() {

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }
        log_info << "S3 module starting";

        // Start worker thread
        boost::asio::post(_pool, [this] { _s3Worker->Start(); });
        boost::asio::post(_pool, [this] { _s3Monitoring->Start(); });
        //_s3Worker->Start();

        // Set running
        SetRunning();

        //_pool.join();
    }

    void S3Server::Run() {
    }

    void S3Server::Shutdown() {
        log_debug << "Shutdown initiated, s3";
        _s3Monitoring->Stop();
        StopHttpServer();
    }

    void S3Server::CreateTransferBucket() {
        if (Core::Configuration::instance().has("awsmock.service.transfer.bucket")) {

            std::string region = Core::Configuration::instance().getString("awsmock.region");
            std::string owner = Core::Configuration::instance().getString("awsmock.user");
            std::string transferBucketName = Core::Configuration::instance().getString("awsmock.service.transfer.bucket");

            if (!BucketExists(region, transferBucketName)) {
                Dto::S3::CreateBucketRequest request = {.region = Core::Configuration::instance().getString("awsmock.region"), .name = transferBucketName, .owner = owner};
                Dto::S3::CreateBucketResponse response = _s3Service.CreateBucket(request);
                log_info << "Transfer bucket created, arn: " << response.arn;
            }
        }
    }

    bool S3Server::BucketExists(const std::string &region, const std::string &bucketName) {

        try {

            Dto::S3::GetMetadataRequest metaRequest = {.region = region, .bucket = bucketName};
            Dto::S3::GetMetadataResponse metaResponse = _s3Service.GetBucketMetadata(metaRequest);
            log_debug << "Transfer bucket exists, bucket: " << metaResponse.bucket;
            return true;

        } catch (Core::NotFoundException &ex) {
            return false;
        }
    }
}// namespace AwsMock::Service
