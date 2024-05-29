
#include "awsmock/core/exception/UnauthorizedException.h"
#include <awsmock/service/dynamodb/DynamoDbHandler.h>

namespace AwsMock::Service {

    DynamoDbHandler::DynamoDbHandler() {

        _secretAccessKey = Core::Configuration::instance().getString("awsmock.secret.access.key", "none");
    }

    http::response<http::string_body> DynamoDbHandler::HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_trace << "DynamoDb POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::DynamoDbClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            switch (clientCommand.command) {

                case Dto::Common::DynamoDbCommandType::CREATE_TABLE: {

                    Dto::DynamoDb::CreateTableRequest tableRequest;
                    tableRequest.FromJson(clientCommand.payload);
                    tableRequest.region = clientCommand.region;
                    tableRequest.requestId = clientCommand.requestId;
                    tableRequest.user = clientCommand.user;
                    tableRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::CreateTableResponse tableResponse = _dynamoDbService.CreateTable(tableRequest);

                    if (tableResponse.status == http::status::ok) {
                        return SendOkResponse(request, tableResponse.body, tableResponse.headers);
                    } else {
                        return SendInternalServerError(request, tableResponse.body, tableResponse.headers);
                    }
                    log_info << "Table created, name: " << tableRequest.tableName;

                    break;
                }

                case Dto::Common::DynamoDbCommandType::LIST_TABLES: {

                    Dto::DynamoDb::ListTableRequest tableRequest;
                    tableRequest.FromJson(clientCommand.payload);
                    tableRequest.region = clientCommand.region;
                    tableRequest.requestId = clientCommand.requestId;
                    tableRequest.user = clientCommand.user;
                    tableRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::ListTableResponse tableResponse = _dynamoDbService.ListTables(tableRequest);
                    if (tableResponse.status == http::status::ok) {
                        return SendOkResponse(request, tableResponse.body, tableResponse.headers);
                    } else {
                        return SendInternalServerError(request, tableResponse.body, tableResponse.headers);
                    }
                    log_info << "Table listed, region: " << tableRequest.region;

                    break;
                }

                case Dto::Common::DynamoDbCommandType::DESCRIBE_TABLE: {

                    Dto::DynamoDb::DescribeTableRequest tableRequest;
                    tableRequest.FromJson(clientCommand.payload);
                    tableRequest.region = clientCommand.region;
                    tableRequest.requestId = clientCommand.requestId;
                    tableRequest.user = clientCommand.user;
                    tableRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::DescribeTableResponse tableResponse = _dynamoDbService.DescribeTable(tableRequest);
                    if (tableResponse.status == http::status::ok) {
                        return SendOkResponse(request, tableResponse.body, tableResponse.headers);
                    } else {
                        return SendInternalServerError(request, tableResponse.body, tableResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::DELETE_TABLE: {

                    Dto::DynamoDb::DeleteTableRequest tableRequest;
                    tableRequest.FromJson(clientCommand.payload);
                    tableRequest.region = clientCommand.region;
                    tableRequest.requestId = clientCommand.requestId;
                    tableRequest.user = clientCommand.user;
                    tableRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::DeleteTableResponse tableResponse = _dynamoDbService.DeleteTable(tableRequest);
                    if (tableResponse.status == http::status::ok) {
                        return SendOkResponse(request, tableResponse.body, tableResponse.headers);
                    } else {
                        return SendInternalServerError(request, tableResponse.body, tableResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::GET_ITEM: {

                    Dto::DynamoDb::GetItemRequest itemRequest;
                    itemRequest.FromJson(clientCommand.payload);
                    itemRequest.region = clientCommand.region;
                    itemRequest.requestId = clientCommand.requestId;
                    itemRequest.user = clientCommand.user;
                    itemRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::GetItemResponse itemResponse = _dynamoDbService.GetItem(itemRequest);
                    if (itemResponse.status == http::status::ok) {
                        return SendOkResponse(request, itemResponse.body, itemResponse.headers);
                    } else {
                        return SendInternalServerError(request, itemResponse.body, itemResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::PUT_ITEM: {

                    Dto::DynamoDb::PutItemRequest itemRequest;
                    itemRequest.FromJson(clientCommand.payload);
                    itemRequest.region = clientCommand.region;
                    itemRequest.requestId = clientCommand.requestId;
                    itemRequest.user = clientCommand.user;
                    itemRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::PutItemResponse itemResponse = _dynamoDbService.PutItem(itemRequest);
                    if (itemResponse.status == http::status::ok) {
                        return SendOkResponse(request, itemResponse.body, itemResponse.headers);
                    } else {
                        return SendInternalServerError(request, itemResponse.body, itemResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::QUERY: {

                    Dto::DynamoDb::QueryRequest queryRequest;
                    queryRequest.FromJson(clientCommand.payload);
                    queryRequest.region = clientCommand.region;
                    queryRequest.requestId = clientCommand.requestId;
                    queryRequest.user = clientCommand.user;
                    queryRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::QueryResponse queryResponse = _dynamoDbService.Query(queryRequest);
                    if (queryResponse.status == http::status::ok) {
                        return SendOkResponse(request, queryResponse.body, queryResponse.headers);
                    } else {
                        return SendInternalServerError(request, queryResponse.body, queryResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::SCAN: {

                    Dto::DynamoDb::ScanRequest scanRequest;
                    scanRequest.FromJson(clientCommand.payload);
                    scanRequest.region = clientCommand.region;
                    scanRequest.requestId = clientCommand.requestId;
                    scanRequest.user = clientCommand.user;
                    scanRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::ScanResponse scanResponse = _dynamoDbService.Scan(scanRequest);
                    if (scanResponse.status == http::status::ok) {
                        return SendOkResponse(request, scanResponse.body, scanResponse.headers);
                    } else {
                        return SendInternalServerError(request, scanResponse.body, scanResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::DELETE_ITEM: {

                    Dto::DynamoDb::DeleteItemRequest dynamoDbRequest;
                    dynamoDbRequest.FromJson(clientCommand.payload);
                    dynamoDbRequest.region = clientCommand.region;
                    dynamoDbRequest.requestId = clientCommand.requestId;
                    dynamoDbRequest.user = clientCommand.user;
                    dynamoDbRequest.headers = clientCommand.headers;

                    Dto::DynamoDb::DeleteItemResponse dynamoDbResponse = _dynamoDbService.DeleteItem(dynamoDbRequest);
                    if (dynamoDbResponse.status == http::status::ok) {
                        return SendOkResponse(request, dynamoDbResponse.body, dynamoDbResponse.headers);
                    } else {
                        return SendInternalServerError(request, dynamoDbResponse.body, dynamoDbResponse.headers);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::UNKNOWN: {
                    log_error << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command);
                    return SendBadRequestError(request, "Bad request, method: POST clientCommand: " + Dto::Common::DynamoDbCommandTypeToString(clientCommand.command));
                }

                default: {
                    log_error << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command);
                    return SendBadRequestError(request);
                }
            }

        } catch (Poco::Exception &exc) {
            return SendInternalServerError(request, exc.message());
        }
        return SendBadRequestError(request);
    }

}// namespace AwsMock::Service
