
#include "awsmock/controller/ResourceNotFound.h"

namespace AwsMock {

  void ResourceNotFound::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    response.setReason(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
    response.setContentType("application/json; charset=utf-8");

    Dto::Common::RestErrorResponse errorResponse;
    errorResponse.code = 404;
    errorResponse.message = "Resource not found";
    errorResponse.resource = request.getURI();

    std::ostream &outputStream = response.send();
    outputStream << errorResponse.ToXml();
    outputStream.flush();
  }
}
