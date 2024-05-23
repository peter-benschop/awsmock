//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/dynamodb/DynamoDbService.h>

namespace AwsMock::Service {

    DynamoDbService::DynamoDbService(Core::Configuration &configuration) : _configuration(configuration), _dynamoDbDatabase(Database::DynamoDbDatabase::instance()) {

        // DynamoDB docker host, port
        _dockerHost = "localhost";
        _dockerPort = _configuration.getInt("awsmock.dynamodb.port");
    }

    Dto::DynamoDb::CreateTableResponse DynamoDbService::CreateTable(const Dto::DynamoDb::CreateTableRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "create_table");
        log_debug << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName;

        if (_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table exists already, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already");
        }

        Dto::DynamoDb::CreateTableResponse createTableResponse;
        try {

            Database::Entity::DynamoDb::Table table = {
                    .region = request.region,
                    .name = request.tableName,
                    .attributes = request.attributes,
                    .tags = request.tags,
                    .keySchemas = request.keySchemas};

            // Send request to DynamoDB docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            createTableResponse = {.body = response.body, .headers = response.headers, .status = response.status};

            // Update database
            table = _dynamoDbDatabase.CreateTable(table);
            log_info << "DynamoDb table created, name: " << table.name;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd create table failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDbd create table failed, error: " + exc.message());
        }

        return createTableResponse;
    }

    Dto::DynamoDb::ListTableResponse DynamoDbService::ListTables(const Dto::DynamoDb::ListTableRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "list_tables");
        log_debug << "Starting list table request, region: " << request.region;

        Dto::DynamoDb::ListTableResponse listTableResponse;
        try {

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            listTableResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb list tables, region: " << request.region;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd create table failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDbd create table failed, error: " + exc.message());
        }

        return listTableResponse;
    }

    Dto::DynamoDb::DescribeTableResponse DynamoDbService::DescribeTable(const Dto::DynamoDb::DescribeTableRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "describe_table");
        log_debug << "Describe DynamoDb table, region: " << request.region << " name: " << request.tableName;

        Dto::DynamoDb::DescribeTableResponse describeTableResponse;
        describeTableResponse.region = request.region;
        describeTableResponse.tableName = request.tableName;
        describeTableResponse.body = {};

        try {
            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            describeTableResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb describe table, name: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDb describe table failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDb describe table failed, error: " + exc.message());
        }

        return describeTableResponse;
    }

    Dto::DynamoDb::DeleteTableResponse DynamoDbService::DeleteTable(const Dto::DynamoDb::DeleteTableRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "delete_table");
        log_debug << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName;

        if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table does not exist, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::DeleteTableResponse deleteTableResponse;
        try {

            // Send request to DynamoDB docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            deleteTableResponse = {.body = response.body, .headers = response.headers, .status = response.status};

            // Delete table in database
            _dynamoDbDatabase.DeleteTable(request.region, request.tableName);
            log_info << "DynamoDb table deleted, name: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd delete table failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDbd delete table failed, error: " + exc.message());
        }

        return deleteTableResponse;
    }

    void DynamoDbService::DeleteAllTables() {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "delete_all_tables");
        log_debug << "Deleting all tables";

        try {

            // Delete all tables from DynamoDB
            for (auto &table: _dynamoDbDatabase.ListTables()) {

                Dto::DynamoDb::DeleteTableRequest dynamoDeleteRequest;
                dynamoDeleteRequest.tableName = table.name;
                dynamoDeleteRequest.body = dynamoDeleteRequest.ToJson();
                dynamoDeleteRequest.headers["Region"] = "eu-central-1";
                dynamoDeleteRequest.headers["X-Amz-Target"] = "DynamoDB_20120810.DeleteTable";
                dynamoDeleteRequest.headers["User-Agent"] = "aws-cli/2.15.23 Python/3.11.6 Linux/6.1.0-18-amd64 exe/x86_64.debian.12 prompt/off command/dynamodb.delete-table";

                SendDynamoDbRequest(dynamoDeleteRequest.body, dynamoDeleteRequest.headers);
            }

            // Delete table in database
            _dynamoDbDatabase.DeleteAllTables();
            log_info << "DynamoDb tables deleted";

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd delete table failed, message: " << exc.message();
            throw Core::ServiceException("DynamoDbd delete table failed, message: " + exc.message());
        }
    }

    Dto::DynamoDb::GetItemResponse DynamoDbService::GetItem(const Dto::DynamoDb::GetItemRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "get_item");
        log_debug << "Start get item, region: " << request.region << " name: " << request.tableName;

        if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::GetItemResponse getItemResponse;
        try {

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            getItemResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb get item, name: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd get item failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDbd get item failed, , error: " + exc.message());
        }

        return getItemResponse;
    }

    Dto::DynamoDb::PutItemResponse DynamoDbService::PutItem(const Dto::DynamoDb::PutItemRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "put_item");
        log_debug << "Start put item, region: " << request.region << " name: " << request.tableName;

        if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::PutItemResponse putItemResponse;
        try {

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            putItemResponse = {.body = response.body, .headers = response.headers, .status = response.status};

            // Convert to entity and save to database. If no exception is thrown by the HTTP call to the
            // docker image, seems to be ok.
            Database::Entity::DynamoDb::Item item = Dto::DynamoDb::Mapper::map(request);
            item = _dynamoDbDatabase.CreateOrUpdateItem(item);

            log_info << "DynamoDb put item, region: " << item.region << " tableName: " << item.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDb put item failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDb put item failed, error: " + exc.message());
        }

        return putItemResponse;
    }

    Dto::DynamoDb::QueryResponse DynamoDbService::Query(const Dto::DynamoDb::QueryRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "query");
        log_debug << "Start query, region: " << request.region << " name: " << request.tableName;

        if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::QueryResponse queryResponse;
        try {

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            queryResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb query item, name: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDb query failed, error: " << exc.message();
            throw Core::ServiceException("DynamoDb query failed, error: " + exc.message());
        }

        return queryResponse;
    }

    Dto::DynamoDb::ScanResponse DynamoDbService::Scan(const Dto::DynamoDb::ScanRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "scan");
        log_debug << "Start scan, region: " << request.region << " name: " << request.tableName;

        if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
            log_warning << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::ScanResponse scanResponse;
        try {

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            scanResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb query item, name: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDb query failed, message: " << exc.message();
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        return scanResponse;
    }

    Dto::DynamoDb::DeleteItemResponse DynamoDbService::DeleteItem(const Dto::DynamoDb::DeleteItemRequest &request) {
        Core::MetricServiceTimer measure(DYNAMODB_SERVICE_TIMER, "delete_item");
        log_debug << "Start creating a new DynamoDb item, region: " << request.region << " table: " << request.tableName;

        Database::Entity::DynamoDb::Item item = Dto::DynamoDb::Mapper::map(request);

        if (!_dynamoDbDatabase.ItemExists(item)) {
            log_warning << "DynamoDb item does not exist, region: " << request.region << " name: " << request.tableName;
            throw Core::BadRequestException("DynamoDb table exists already, region: " + request.region + " name: " + request.tableName);
        }

        Dto::DynamoDb::DeleteItemResponse deleteItemResponse;
        try {

            // Delete item in database
            _dynamoDbDatabase.DeleteItem(request.region, request.tableName, "");

            // Send request to docker container
            Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
            deleteItemResponse = {.body = response.body, .headers = response.headers, .status = response.status};
            log_info << "DynamoDb item deleted, table: " << request.tableName;

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd delete item failed, message: " << exc.message();
            throw Core::ServiceException("DynamoDbd delete item failed, message: " + exc.message());
        }

        return deleteItemResponse;
    }

    /*void DynamoDbService::DeleteItems(const std::string &region, const std::string &tableName) {
        log_debug << "Deleting all items, table: " << tableName;

        try {
            // Delete table in database
            _dynamoDbDatabase.DeleteAllTables();
            log_info << "DynamoDb tables deleted";

        } catch (Poco::Exception &exc) {
            log_error << "DynamoDbd delete table failed, message: " << exc.message();
            throw Core::ServiceException("DynamoDbd delete table failed, message: " + exc.message());
        }
    }*/

    Dto::DynamoDb::DynamoDbResponse DynamoDbService::SendDynamoDbRequest(const std::string &body, const std::map<std::string, std::string> &headers) {
        log_debug << "Sending DynamoDB container request, endpoint: " << _dockerHost << ":" << _dockerPort;

        Poco::URI uri = Poco::URI("http://" + _dockerHost + ":" + std::to_string(_dockerPort) + "/");
        std::string path(uri.getPathAndQuery());
        log_debug << "Created URI, endpoint: " << path;

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_0);
        log_trace << "DynamoDB request defined, body: " + body;

        // Copy headers
        for (const auto &header: headers) {
            request.add(header.first, header.second);
        }

        // Add AWS v4 authorization header
        Core::AwsUtils::AddAuthorizationHeader(request, "dynamodb", "application/x-amz-json-1.0", "content-type;host;x-amz-date;x-amz-security-token;x-amz-target", body);

        // Send request
        std::istringstream in(body + '\n');
        std::ostream &os = session.sendRequest(request);
        Poco::StreamCopier::copyStream(in, os);
        os.flush();

        // Get the response state
        Poco::Net::HTTPResponse response;
        std::istream &istream = session.receiveResponse(response);
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, status: " << response.getStatus() << " reason: " << response.getReason();
            throw Core::ServiceException("HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason());
        }

        std::stringstream bodyStream;
        Poco::StreamCopier::copyStream(istream, bodyStream);
        log_debug << "DynamoDB request request send, status: " << response.getStatus();

        std::map<std::string, std::string> responseHeaders;
        for (const auto &header: response) {
            responseHeaders[header.first] = header.second;
        }
        return {.body = bodyStream.str(), .headers = responseHeaders, .status = response.getStatus()};
    }

}// namespace AwsMock::Service
