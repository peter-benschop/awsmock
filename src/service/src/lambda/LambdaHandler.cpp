
#include <awsmock/service/lambda/LambdaHandler.h>

namespace AwsMock::Service {

    void LambdaHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Lambda GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

            if (action == "functions") {


                if (Core::HttpUtils::HasPathParameters(request.getURI(), 2)) {

                    std::string functionName = Core::HttpUtils::GetPathParameters(request.getURI())[2];

                    Dto::Lambda::GetFunctionResponse lambdaResponse = _lambdaService.GetFunction(region, functionName);
                    log_trace << "Lambda function region: " << region << " name: " << functionName;
                    SendOkResponse(response, lambdaResponse.ToJson());

                } else {

                    Dto::Lambda::ListFunctionResponse lambdaResponse = _lambdaService.ListFunctions(region);
                    log_trace << "Lambda function list";
                    SendOkResponse(response, lambdaResponse.ToJson());

                }

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                Dto::Lambda::ListTagsResponse lambdaResponse = _lambdaService.ListTags(arn);
                log_trace << "Lambda tag list";
                SendOkResponse(response, lambdaResponse.ToJson());

            }

        } catch (Core::ServiceException &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        } catch (Core::ResourceNotFoundException &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        }
    }

    void LambdaHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response,
                                  [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
        log_trace << "Lambda PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user;

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        }
    }

    void LambdaHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Lambda POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {
            std::string tmp = request.getURI();
            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

            if (action == "functions") {

                std::string body = Core::HttpUtils::GetBodyAsString(request);

                if (Core::HttpUtils::GetPathParameter(request.getURI(), 3) == "invocations") {

                    std::string functionName = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                    log_debug << "Lambda function invocation, name: " << functionName;

                    _lambdaService.InvokeLambdaFunction(functionName, body, region, user);
                    log_info << "Lambda function invoked, name: " << functionName;
                    SendOkResponse(response);

                } else {

                    Dto::Lambda::CreateFunctionRequest lambdaRequest;
                    lambdaRequest.FromJson(body);
                    lambdaRequest.region = region;
                    lambdaRequest.user = user;

                    Dto::Lambda::CreateFunctionResponse lambdaResponse = _lambdaService.CreateFunction(lambdaRequest);
                    log_info << "Lambda function created, name: " << lambdaResponse.functionName;
                    SendOkResponse(response, lambdaResponse.ToJson());
                }

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                std::string body = Core::HttpUtils::GetBodyAsString(request);
                Dto::Lambda::CreateTagRequest lambdaRequest;
                lambdaRequest.FromJson(body);

                _lambdaService.CreateTag(lambdaRequest);
                SendOkResponse(response, {}, Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
                log_info << "Lambda tag created, name: " << lambdaRequest.arn;

            }

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        }
    }

    void LambdaHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Lambda DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {
            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);
            std::string body = Core::HttpUtils::GetBodyAsString(request);

            if (action == "functions") {

                std::string functionName = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                std::string qualifier = Core::HttpUtils::GetPathParameter(request.getURI(), 3);
                log_debug << "Found lambda name, name: " << functionName << " qualifier: " << qualifier;

                Dto::Lambda::DeleteFunctionRequest lambdaRequest = {.functionName=functionName, .qualifier=qualifier};
                _lambdaService.DeleteFunction(lambdaRequest);
                SendOkResponse(response);

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                std::vector<std::string> tagKeys = Core::HttpUtils::GetQueryParametersByPrefix(request.getURI(),
                                                                                               "tagKeys");
                log_trace << "Got tags count: " << tagKeys.size();

                Dto::Lambda::DeleteTagsRequest lambdaRequest(arn, tagKeys);
                _lambdaService.DeleteTags(lambdaRequest);
                SendNoContentResponse(response);

            }

        } catch (Core::ServiceException &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        }
    }

    void LambdaHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        log_trace << "Lambda OPTIONS request";

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void LambdaHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Lambda HEAD request, address: " << request.clientAddress().toString();

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

            HeaderMap headerMap;
            headerMap["Connection"] = "Keep-alive: 300";
            headerMap["Server"] = "AmazonS3";

            SendOkResponse(response, {}, headerMap);

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("lambda", response, exc);
        }
    }
}
