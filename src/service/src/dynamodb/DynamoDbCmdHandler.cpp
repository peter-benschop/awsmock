
#include "awsmock/service/dynamodb/DynamoDbCmdHandler.h"

namespace AwsMock::Service {

    DynamoDbCmdHandler::DynamoDbCmdHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _dynamoDbService(configuration) {
    }

    void DynamoDbCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::DynamoDbClientCommand &clientCommand) {
        log_debug << "DynamoDb POST request, URI: " << request.getURI() << " region: " << clientCommand.region << " user: " << clientCommand.user << " command: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command);

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

                    if (tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, tableResponse.body, tableResponse.headers);
                    } else {
                        SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
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
                    if (tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, tableResponse.body, tableResponse.headers);
                    } else {
                        SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
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
                    if (tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, tableResponse.body, tableResponse.headers);
                    } else {
                        SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
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
                    if (tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, tableResponse.body, tableResponse.headers);
                    } else {
                        SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
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
                    if (itemResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, itemResponse.body, itemResponse.headers);
                    } else {
                        SendErrorResponse(response, itemResponse.body, itemResponse.headers, itemResponse.status);
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
                    if (itemResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, itemResponse.body, itemResponse.headers);
                    } else {
                        SendErrorResponse(response, itemResponse.body, itemResponse.headers, itemResponse.status);
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
                    if (queryResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, queryResponse.body, queryResponse.headers);
                    } else {
                        SendErrorResponse(response, queryResponse.body, queryResponse.headers, queryResponse.status);
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
                    if (scanResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, scanResponse.body, scanResponse.headers);
                    } else {
                        SendErrorResponse(response, scanResponse.body, scanResponse.headers, scanResponse.status);
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
                    if (dynamoDbResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
                        SendOkResponse(response, dynamoDbResponse.body, dynamoDbResponse.headers);
                    } else {
                        SendErrorResponse(response, dynamoDbResponse.body, dynamoDbResponse.headers, dynamoDbResponse.status);
                    }

                    break;
                }

                case Dto::Common::DynamoDbCommandType::UNKNOWN: {
                    log_error << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command);
                    throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::DynamoDbCommandTypeToString(clientCommand.command));
                }

                default: {
                    log_error << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command);
                    SendOkResponse(response);
                }
            }

        } catch (Poco::Exception &exc) {
            SendJsonErrorResponse("DynamoDb", response, exc);
        }
    }
}// namespace AwsMock::Service
