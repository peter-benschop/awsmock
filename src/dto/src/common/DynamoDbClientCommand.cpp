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

        if (!Core::AwsUtils::VerifySignature(request, payload, _secretAccessKey)) {
            log_error << "AWS signature could not be verified";
            throw Core::UnauthorizedException("AWS signature could not be verified");
        }

        switch (method) {
            case HttpMethod::GET:
            case HttpMethod::PUT:
            case HttpMethod::DELETE:
                break;
            case HttpMethod::POST:
                command = GetClientCommandFromHeader(request);
                break;
            case HttpMethod::HEAD:
            case HttpMethod::UNKNOWN: {
                break;
            }
        }
    }

    DynamoDbCommandType DynamoDbClientCommand::GetClientCommandFromHeader(const Poco::Net::HTTPServerRequest &request) {

        if (request.has("X-Amz-Target")) {
            std::string headerValue = request.get("X-Amz-Target");
            std::string action = Core::StringUtils::Split(headerValue, '.')[1];
            return DynamoDbCommandTypeFromString(action);
        }
        return DynamoDbCommandType::UNKNOWN;
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
            log_error << exc.message();
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
