
#include "awsmock/service/sqs/SQSHandler.h"

namespace AwsMock::Service {

  SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService) : SQSCmdHandler(configuration, metricService), _logger(Poco::Logger::get("SQSHandler")) {
  }

  void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SQS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Dto::Common::SQSClientCommand clientCommand;
    clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

    SQSCmdHandler::handlePost(request, response, clientCommand);
  }
}
