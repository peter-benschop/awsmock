
#include <awsmock/service/lambda/LambdaHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> LambdaHandler::HandleGetRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "Lambda GET request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {

            std::map<std::string, std::string> headers = Core::HttpUtils::GetHeaders(request);

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.target(), version, action);

            if (action == "functions") {


                if (Core::HttpUtils::HasPathParameters(request.target(), 2)) {

                    std::string functionName = Core::HttpUtils::GetPathParameters(request.target())[2];

                    Dto::Lambda::GetFunctionResponse lambdaResponse = _lambdaService.GetFunction(region, functionName);
                    log_trace << "Lambda function region: " << region << " name: " << functionName;
                    return SendOkResponse(request, lambdaResponse.ToJson());

                } else {

                    Dto::Lambda::ListFunctionResponse lambdaResponse = _lambdaService.ListFunctions(region);
                    log_trace << "Lambda function list";
                    return SendOkResponse(request, lambdaResponse.ToJson());
                }

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.target(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                Dto::Lambda::ListTagsResponse lambdaResponse = _lambdaService.ListTags(arn);
                log_trace << "Lambda tag list";
                return SendOkResponse(request, lambdaResponse.ToJson());

            } else if (action == "account-settings") {

                Dto::Lambda::AccountSettingsResponse lambdaResponse = _lambdaService.GetAccountSettings();
                log_trace << "Lambda account settings";
                return SendOkResponse(request, lambdaResponse.ToJson());

            } else {
                return SendBadRequestError(request, "Unknown method");
            }

        } catch (Core::ServiceException &exc) {
            return Core::HttpUtils::InternalServerError(request, exc.message());
        } catch (Core::NotFoundException &exc) {
            return SendInternalServerError(request, exc.message());
        }
    }

    http::response<http::dynamic_body> LambdaHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "Lambda POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {
            std::map<std::string, std::string> headers = Core::HttpUtils::GetHeaders(request);

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.target(), version, action);

            if (action == "functions") {

                std::string body = Core::HttpUtils::GetBodyAsString(request);

                if (Core::HttpUtils::GetPathParameter(request.target(), 3) == "invocations") {

                    std::string logType = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Log-Type");

                    std::string functionName = Core::HttpUtils::GetPathParameter(request.target(), 2);
                    log_debug << "Lambda function invocation, name: " << functionName;

                    std::string output = _lambdaService.InvokeLambdaFunction(functionName, body, region, user, logType);
                    log_info << "Lambda function invoked, name: " << functionName;

                    // Set output, if existing
                    if (!output.empty()) {
                        //  response.set("X-Amz-Log-Result", output);
                    }
                    return SendOkResponse(request);

                } else {

                    Dto::Lambda::CreateFunctionRequest lambdaRequest;
                    lambdaRequest.FromJson(body);
                    lambdaRequest.region = region;
                    lambdaRequest.user = user;

                    Dto::Lambda::CreateFunctionResponse lambdaResponse = _lambdaService.CreateFunction(lambdaRequest);
                    log_info << "Lambda function created, name: " << lambdaResponse.functionName;
                    return SendOkResponse(request, lambdaResponse.ToJson());
                }

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.target(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                std::string body = Core::HttpUtils::GetBodyAsString(request);
                Dto::Lambda::CreateTagRequest lambdaRequest;
                lambdaRequest.FromJson(body);

                _lambdaService.CreateTag(lambdaRequest);
                return SendNoContentResponse(request);
                log_info << "Lambda tag created, name: " << lambdaRequest.arn;

            } else {
                log_error << "Unknown method";
                return SendBadRequestError(request, "Unknown method");
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        }
        log_error << "Unknown method";
        return SendBadRequestError(request, "Unknown method");
    }

    http::response<http::dynamic_body> LambdaHandler::HandleDeleteRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "Lambda DELETE request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {
            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.target(), version, action);
            std::string body = Core::HttpUtils::GetBodyAsString(request);

            if (action == "functions") {

                std::string functionName = Core::HttpUtils::GetPathParameter(request.target(), 2);
                std::string qualifier = Core::HttpUtils::GetPathParameter(request.target(), 3);
                log_debug << "Found lambda name, name: " << functionName << " qualifier: " << qualifier;

                Dto::Lambda::DeleteFunctionRequest lambdaRequest = {.functionName = functionName, .qualifier = qualifier};
                _lambdaService.DeleteFunction(lambdaRequest);
                return SendOkResponse(request);

            } else if (action == "tags") {

                std::string arn = Core::HttpUtils::GetPathParameter(request.target(), 2);
                log_debug << "Found lambda arn, arn: " << arn;

                std::vector<std::string> tagKeys = Core::HttpUtils::GetQueryParametersByPrefix(request.target(),
                                                                                               "tagKeys");
                log_trace << "Got tags count: " << tagKeys.size();

                Dto::Lambda::DeleteTagsRequest lambdaRequest(arn, tagKeys);
                _lambdaService.DeleteTags(lambdaRequest);
                return SendNoContentResponse(request);

            } else {
                log_error << "Unknown method";
                return SendBadRequestError(request, "Unknown method");
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        }
    }

}// namespace AwsMock::Service
