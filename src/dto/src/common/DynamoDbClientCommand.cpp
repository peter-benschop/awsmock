//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/DynamoDbClientCommand.h>

namespace AwsMock::Dto::Common {

    void DynamoDbClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

        // Basic values
        this->region = region;
        this->user = user;
        this->method = method;
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->url = request.getURI();
        this->payload = Core::HttpUtils::GetBodyAsString(request);
        this->headers = Core::HttpUtils::GetHeaders(request);

        // Command
        std::string action = request.get("X-Amz-Target");

        switch (method) {
            case HttpMethod::GET:
            case HttpMethod::PUT:
            case HttpMethod::DELETE:
                break;
            case HttpMethod::POST:
                if (Core::StringUtils::ContainsIgnoreCase(action, "CreateTable")) {
                    command = DynamoDbCommandType::CREATE_TABLE;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "ListTables")) {
                    command = DynamoDbCommandType::LIST_TABLES;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "DescribeTable")) {
                    command = DynamoDbCommandType::DESCRIBE_TABLE;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "DeleteTable")) {
                    command = DynamoDbCommandType::DELETE_TABLE;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "PutItem")) {
                    command = DynamoDbCommandType::PUT_ITEM;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "GetItem")) {
                    command = DynamoDbCommandType::GET_ITEM;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "Query")) {
                    command = DynamoDbCommandType::QUERY;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "Scan")) {
                    command = DynamoDbCommandType::SCAN;
                }
                break;
            case HttpMethod::UNKNOWN: {
                break;
            }
        }
    }

    std::string DynamoDbClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", HttpMethodToString(method));
            rootJson.set("command", DynamoDbCommandTypeToString(command));
            rootJson.set("user", user);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string DynamoDbClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DynamoDbClientCommand &r) {
        os << "DynamoDbClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
