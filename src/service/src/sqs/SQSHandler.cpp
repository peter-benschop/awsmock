
#include "awsmock/service/SQSHandler.h"

namespace AwsMock::Service {

  SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : SQSCliHandler(configuration, metricService, condition), SQSCppHandler(configuration, metricService, condition),
                                                                                                                               SQSJava1Handler(configuration, metricService, condition), SQSJava2Handler(configuration, metricService, condition),
                                                                                                                               _logger(Poco::Logger::get("SQSHandler")) {
  }

  void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SQS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "sqs");

      switch (userAgent.type) {
      case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:
      case Dto::Common::UserAgentType::AWS_CLI: return SQSCliHandler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA1: return SQSJava1Handler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return SQSJava2Handler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_CPP: return SQSCppHandler::handlePost(request, response, region, user);

      }

    } catch (Core::ServiceException &exc) {
      _logger.error() << "SQS module exception: " << exc.message() << std::endl;
      SendXmlErrorResponse("SQS", response, exc);
    }
  }

  void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {

    log_debug_stream(_logger) << "SQS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SQSHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
