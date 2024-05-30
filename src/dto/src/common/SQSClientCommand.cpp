//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SQSClientCommand.h>

namespace AwsMock::Dto::Common {

    void SQSClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request);

        // Basic values
        this->method = request.method();
        this->region = awsRegion;
        this->user = awsUser;
        this->url = request.target();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString1(request);
        this->headers = Core::HttpUtils::GetHeaders(request);
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());

        if (userAgent.clientCommand.empty()) {

            this->command = Dto::Common::SqsCommandTypeFromString(GetCommandFromHeader(request));

        } else {

            this->command = Dto::Common::SqsCommandTypeFromString(userAgent.clientCommand);
        }
    }

    std::string SQSClientCommand::GetCommandFromHeader(const http::request<http::dynamic_body> &request) const {

        std::string cmd;
        std::string cType = request["Content-Type"];
        if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-www-form-urlencoded")) {

            cmd = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

        } else if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-amz-json-1.0")) {

            std::string headerValue = request["X-Amz-Target"];
            cmd = Core::StringUtils::Split(headerValue, '.')[1];
        }
        return Core::StringUtils::ToSnakeCase(cmd);
    }

    std::string SQSClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", boost::lexical_cast<std::string>(method));
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("url", url);
            rootJson.set("contentType", contentType);
            rootJson.set("payload", payload);
            rootJson.set("command", SqsCommandTypeToString(command));

            // Headers
            Poco::JSON::Array jsonHeaders;
            for (const auto &header: headers) {
                Poco::JSON::Object jsonHeader;
                jsonHeader.set(header.first, header.second);
                jsonHeaders.add(jsonHeader);
            }
            rootJson.set("headers", jsonHeaders);

            return Core::JsonUtils::ToJsonString(rootJson, true);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SQSClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SQSClientCommand &r) {
        os << "SQSClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
