//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/TransferServer.h"

namespace AwsMock::Service {

    TransferServer::TransferServer(Core::Configuration &configuration, Core::MetricService &metricService)
        : _logger("TransferServer"), _configuration(configuration), _metricService(metricService) {

        _port = _configuration.getInt("awsmock.service.transfer.port", TRANSFER_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.transfer.host", TRANSFER_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.transfer.max.queue", 250);
        _maxThreads = _configuration.getInt("awsmock.service.transfer.max.threads", 50);
        log_debug_stream(_logger) << "Transfer rest service initialized, endpoint: " << _host << ":" << _port << std::endl;
    }

    TransferServer::~TransferServer() {
        if(_httpServer) {
            _httpServer->stopAll(true);
            delete _httpServer;
            log_info_stream(_logger) << "Transfer rest service stopped" << std::endl;
        }
    }

    void TransferServer::start() {

        // Set HTTP server parameter
        auto *httpServerParams = new Poco::Net::HTTPServerParams();
        httpServerParams->setMaxQueued(_maxQueueLength);
        httpServerParams->setMaxThreads(_maxThreads);
        log_debug_stream(_logger) << "HTTP server parameter set, maxQueue: " << _maxQueueLength << " maxThreads: " << _maxThreads << std::endl;

        _httpServer =
            new Poco::Net::HTTPServer(new TransferRequestHandlerFactory(_configuration, _metricService), Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

        _httpServer->start();
        log_info_stream(_logger) << "Transfer rest service started, endpoint: http://" << _host << ":" << _port << std::endl;
    }
}
