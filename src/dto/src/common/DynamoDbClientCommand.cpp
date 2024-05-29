//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/DynamoDbClientCommand.h>

namespace AwsMock::Dto::Common {

    void DynamoDbClientCommand::FromRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {

        // Basic values
        this->region = region;
        this->user = user;
        this->method = method;
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->url = request.target();
        this->payload = request.body();
        this->headers = Core::HttpUtils::GetHeaders(request);

        switch (method) {
            case http::verb::post:
                command = GetClientCommandFromHeader(request);
                break;
            case http::verb::get:
            case http::verb::put:
            case http::verb::delete_:
            case http::verb::head:
                break;
        }
    }

    DynamoDbCommandType DynamoDbClientCommand::GetClientCommandFromHeader(const http::request<http::string_body> &request) {

        if (Core::HttpUtils::HasHeader(request, "X-Amz-Target")) {
            std::string headerValue = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
            std::string action = Core::StringUtils::Split(headerValue, '.')[1];
            return DynamoDbCommandTypeFromString(action);
        }
        return DynamoDbCommandType::UNKNOWN;
    }

    std::string DynamoDbClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", boost::lexical_cast<std::string>(method));
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
