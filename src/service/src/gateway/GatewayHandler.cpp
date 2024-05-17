
#include <awsmock/service/gateway/GatewayHandler.h>

#include <utility>

namespace AwsMock::Service {

    template<class F, class REQ, class RES, class REG, class USR>
    void CallAsyncGet(F &&fun, REQ &&request, RES &&response, REG &&region, USR &&user) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &request, &response, &region, &user]() {
            fun.handleGet(request, response, region, user);
        }))).reset();
    }

    template<class F, class REQ, class RES, class REG, class USR>
    void CallAsyncPut(F &&fun, REQ &&request, RES &&response, REG &&region, USR &&user) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &request, &response, &region, &user]() {
            fun.handlePut(request, response, region, user);
        }))).reset();
    }

    template<class F, class REQ, class RES, class REG, class USR>
    void CallAsyncPost(F &&fun, REQ &&request, RES &&response, REG &&region, USR &&user) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &request, &response, &region, &user]() {
            fun.handlePost(request, response, region, user);
        }))).reset();
    }

    template<class F, class REQ, class RES, class REG, class USR>
    void CallAsyncDelete(F &&fun, REQ &&request, RES &&response, REG &&region, USR &&user) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &request, &response, &region, &user]() {
            fun.handleDelete(request, response, region, user);
        }))).reset();
    }

    template<class F, class REQ, class RES, class REG, class USR>
    void CallAsyncHead(F &&fun, REQ &&request, RES &&response, REG &&region, USR &&user) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &request, &response, &region, &user]() {
            fun.handleHead(request, response, region, user);
        }))).reset();
    }

    GatewayHandler::GatewayHandler(Core::Configuration &configuration, Service::GatewayRoute route) : AbstractHandler(), _configuration(configuration), _route(std::move(route)) {}

    void GatewayHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Gateway GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << " remoteAddress: " << request.clientAddress().toString();

        Core::MetricServiceTimer measure(GATEWAY_GET_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
        log_debug << "Gateway GET request, URI: " + request.getURI() << " region: " << region << " user: " << user;

        SetHeaders(request, region, user);
        switch (_route._handlerType) {

            case S3: {
                CallAsyncGet(S3Handler(_configuration), request, response, region, user);
                break;
            }

            case SQS: {
                CallAsyncGet(SQSHandler(_configuration), request, response, region, user);
                break;
            }

            case SNS: {
                CallAsyncGet(SNSHandler(_configuration), request, response, region, user);
                break;
            }

            case LAMBDA: {
                CallAsyncGet(LambdaHandler(_configuration), request, response, region, user);
                break;
            }

            case TRANSFER: {
                CallAsyncGet(TransferHandler(_configuration), request, response, region, user);
                break;
            }

            case COGNITO: {
                CallAsyncGet(CognitoHandler(_configuration), request, response, region, user);
                break;
            }

            case DYNAMODB: {
                CallAsyncGet(DynamoDbHandler(_configuration), request, response, region, user);
                break;
            }

            case SECRETS_MANAGER: {
                CallAsyncGet(SecretsManagerHandler(_configuration), request, response, region, user);
                break;
            }

            case KMS: {
                CallAsyncGet(KMSHandler(_configuration), request, response, region, user);
                break;
            }
        }
    }

    void GatewayHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Gateway PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << " remoteAddress: " << request.clientAddress().toString();

        Core::MetricServiceTimer measure(GATEWAY_PUT_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
        log_debug << "Gateway PUT request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        SetHeaders(request, region, user);
        switch (_route._handlerType) {

            case S3: {
                CallAsyncPut(S3Handler(_configuration), request, response, region, user);
                break;
            }

            case SQS: {
                CallAsyncPut(SQSHandler(_configuration), request, response, region, user);
                break;
            }

            case SNS: {
                CallAsyncPut(SNSHandler(_configuration), request, response, region, user);
                break;
            }

            case LAMBDA: {
                CallAsyncPut(LambdaHandler(_configuration), request, response, region, user);
                break;
            }

            case TRANSFER: {
                CallAsyncPut(TransferHandler(_configuration), request, response, region, user);
                break;
            }

            case COGNITO: {
                CallAsyncPut(CognitoHandler(_configuration), request, response, region, user);
                break;
            }

            case DYNAMODB: {
                CallAsyncPut(DynamoDbHandler(_configuration), request, response, region, user);
                break;
            }
            case SECRETS_MANAGER: {
                CallAsyncPut(SecretsManagerHandler(_configuration), request, response, region, user);
                break;
            }
            case KMS:
                CallAsyncPut(KMSHandler(_configuration), request, response, region, user);
                break;
        }
    }

    void GatewayHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Gateway POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " remoteAddress: " << request.clientAddress().toString();

        Core::MetricServiceTimer measure(GATEWAY_POST_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
        log_trace << "Gateway POST request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        SetHeaders(request, region, user);
        switch (_route._handlerType) {

            case S3: {
                CallAsyncPost(S3Handler(_configuration), request, response, region, user);
                break;
            }

            case SQS: {
                CallAsyncPost(SQSHandler(_configuration), request, response, region, user);
                break;
            }

            case SNS: {
                CallAsyncPost(SNSHandler(_configuration), request, response, region, user);
                break;
            }

            case LAMBDA: {
                CallAsyncPost(LambdaHandler(_configuration), request, response, region, user);
                break;
            }

            case TRANSFER: {
                CallAsyncPost(TransferHandler(_configuration), request, response, region, user);
                break;
            }

            case COGNITO: {
                CallAsyncPost(CognitoHandler(_configuration), request, response, region, user);
                break;
            }

            case DYNAMODB: {
                CallAsyncPost(DynamoDbHandler(_configuration), request, response, region, user);
                break;
            }

            case SECRETS_MANAGER: {
                CallAsyncPost(SecretsManagerHandler(_configuration), request, response, region, user);
                break;
            }

            case KMS:
                CallAsyncPost(KMSHandler(_configuration), request, response, region, user);
                break;
        }
    }

    void GatewayHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Gateway DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << " remoteAddress: " << request.clientAddress().toString();

        Core::MetricServiceTimer measure(GATEWAY_DELETE_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
        log_debug << "Gateway DELETE request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        SetHeaders(request, region, user);
        switch (_route._handlerType) {

            case S3: {
                CallAsyncDelete(S3Handler(_configuration), request, response, region, user);
                break;
            }

            case SQS: {
                CallAsyncDelete(SQSHandler(_configuration), request, response, region, user);
                break;
            }

            case SNS: {
                CallAsyncDelete(SNSHandler(_configuration), request, response, region, user);
                break;
            }

            case LAMBDA: {
                CallAsyncDelete(LambdaHandler(_configuration), request, response, region, user);
                break;
            }

            case TRANSFER: {
                CallAsyncDelete(TransferHandler(_configuration), request, response, region, user);
                break;
            }

            case COGNITO: {
                CallAsyncDelete(CognitoHandler(_configuration), request, response, region, user);
                break;
            }

            case DYNAMODB: {
                CallAsyncDelete(DynamoDbHandler(_configuration), request, response, region, user);
                break;
            }

            case SECRETS_MANAGER: {
                CallAsyncDelete(SecretsManagerHandler(_configuration), request, response, region, user);
                break;
            }

            case KMS:
                CallAsyncDelete(KMSHandler(_configuration), request, response, region, user);
                break;
        }
    }

    void GatewayHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "Gateway HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << " remoteAddress: " << request.clientAddress().toString();

        Core::MetricServiceTimer measure(GATEWAY_HEAD_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
        log_debug << "Gateway HEAD request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        SetHeaders(request, region, user);
        switch (_route._handlerType) {

            case S3: {
                CallAsyncHead(S3Handler(_configuration), request, response, region, user);
                break;
            }

            case SQS: {
                CallAsyncHead(SQSHandler(_configuration), request, response, region, user);
                break;
            }

            case SNS: {
                CallAsyncHead(SNSHandler(_configuration), request, response, region, user);
                break;
            }

            case LAMBDA: {
                CallAsyncHead(LambdaHandler(_configuration), request, response, region, user);
                break;
            }

            case TRANSFER: {
                CallAsyncHead(TransferHandler(_configuration), request, response, region, user);
                break;
            }

            case COGNITO: {
                CallAsyncHead(CognitoHandler(_configuration), request, response, region, user);
                break;
            }

            case DYNAMODB: {
                CallAsyncHead(DynamoDbHandler(_configuration), request, response, region, user);
                break;
            }

            case SECRETS_MANAGER: {
                CallAsyncHead(SecretsManagerHandler(_configuration), request, response, region, user);
                break;
            }

            case KMS:
                CallAsyncHead(KMSHandler(_configuration), request, response, region, user);
                break;
        }
    }

    void GatewayHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        log_debug << "Gateway OPTIONS request";

        Core::MetricServiceTimer measure(GATEWAY_OPTIONS_TIMER);
        _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void GatewayHandler::SetHeaders(Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {
        log_trace << "Setting request header values, region: " << region << " user: " << user;

        // Default headers
        request.set("Region", region);
        request.set("User", user);
        request.set("RequestId", Core::AwsUtils::CreateRequestId());
    }

}// namespace AwsMock::Service
